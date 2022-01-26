/*************************************************************************
	> File Name: main.cpp
	> Author: Nefelibata
	> Mail: csehuyi@whu.edu.cn 
	> Created Time: Fri 21 Jan 2022 04:11:47 PM CST
 ************************************************************************/
#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<iostream>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<cstring>
#include "utils.h"
#include<sys/select.h>

using namespace std;

int main(){
	int sockfd = socket(AF_INET, SOCK_STREAM, 0);
	//参数， 第一个表示ip地址类型， ipv4: AF_INET ipv6:AF_INET6
	//第二个表示数据传输方式 TCP: SOCK_STREAM UDP: SOCK_DGRAM
	//协议， 0表示自动推导， 可以设置为IPPROTO_TCP 和IPPROTO_UDP
	errif(sockfd == -1, "socket create error!");	
	struct sockaddr_in serv_addr;
	bzero(&serv_addr, sizeof(serv_addr));
	
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	serv_addr.sin_port = htons(8888);
	
	errif(bind(sockfd, (sockaddr*)&serv_addr, sizeof(serv_addr)) == -1, "socket bind error!");
	
	errif(listen(sockfd, SOMAXCONN) == -1, "socket listen error");

	//struct sockaddr_in clnt_addr;
	//socklen_t clnt_addr_len = sizeof(clnt_addr);
	//bzero(&clnt_addr, sizeof(clnt_addr));
	//int clnt_sockfd = accept(sockfd, (sockaddr*)&clnt_addr,&clnt_addr_len);
	//errif(clnt_sockfd == -1, "socket accept error!");	
	//cout<<"new client fd "<< clnt_sockfd << "! IP: " << inet_ntoa(clnt_addr.sin_addr) << " Port: " << ntohs(clnt_addr.sin_port) << endl;

	int ret = 0;
	char buf[1024];
	fd_set read_fds;
	
	int client_fds[5];
	int conn_fd = 0;
	int maxsock = sockfd;

	bzero((void*)client_fds, sizeof(client_fds));
	while(true){
		FD_ZERO(&read_fds);
		FD_SET(sockfd, &read_fds);
		/*
		 * 每次调用select都要重新在read_fds和exception_fds中设置文件描述符clnt_sockfd
		 * 事件发生后，文件描述符集合将被内核修改
		 */
		for(int i = 0; i < 5; i++){
			if(client_fds[i] != 0){
				//cout<<"set client:"<<client_fds[i];
				FD_SET(client_fds[i], &read_fds);
			}
		}
		//cout<<endl;
		//cout<<"maxsock:"<<maxsock<<endl;
		ret = select(maxsock+1, &read_fds, NULL, NULL, NULL);
		if(ret < 0){
			cout<<"selection failure"<<endl;
			break;
		}
		cout<<"ready fd:"<<ret<<endl;
		//对于可读事件， 采用recv函数读取数据
		for(int i = 0; i < conn_fd; i++){
			if(FD_ISSET(client_fds[i], &read_fds)){
				ret = recv(client_fds[i], buf, sizeof(buf), 0);
				if(ret <= 0){
					break;
				}
				cout << "get " << ret << " bytes of normal data:" << buf << "from client:" << i <<endl;
			
				write(client_fds[i], buf, sizeof(buf));
			}
		}
		if(FD_ISSET(sockfd, &read_fds)){
			struct sockaddr_in clnt_addr;
			socklen_t clnt_addr_len = sizeof(clnt_addr);
			bzero(&clnt_addr, sizeof(clnt_addr));
			int clnt_sockfd = accept(sockfd, (sockaddr*)&clnt_addr,&clnt_addr_len);
			errif(clnt_sockfd == -1, "socket accept error!");
			if(conn_fd < 5){
				client_fds[conn_fd++] = clnt_sockfd;
				bzero(&buf, sizeof(buf));
				maxsock = maxsock > clnt_sockfd ? maxsock : clnt_sockfd;
				cout<<"new client fd "<< clnt_sockfd << "! IP: " << inet_ntoa(clnt_addr.sin_addr) << " Port: " << ntohs(clnt_addr.sin_port) << endl;
			}
		}
	}
	return 0;
}
