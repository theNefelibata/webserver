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

	struct sockaddr_in clnt_addr;
	socklen_t clnt_addr_len = sizeof(clnt_addr);
	bzero(&clnt_addr, sizeof(clnt_addr));
	int clnt_sockfd = accept(sockfd, (sockaddr*)&clnt_addr,&clnt_addr_len);
	errif(clnt_sockfd == -1, "socket accept error!");	
	cout<<"new client fd "<< clnt_sockfd << "! IP: " << inet_ntoa(clnt_addr.sin_addr) << " Port: " << ntohs(clnt_addr.sin_port) << endl;
	
	while(true){
		char buf[1024];
		bzero(&buf, sizeof(buf));
		ssize_t read_bytes = read(clnt_sockfd, buf, sizeof(buf));
		if(read_bytes > 0){
			cout<<"message from client fd "<<clnt_sockfd<<" : "<<buf<<endl;
			write(clnt_sockfd, buf, sizeof(buf));
		}else if(read_bytes == 0){
			cout<<"client fd "<<clnt_sockfd<<" disconnected"<<endl;
			close(clnt_sockfd);
			break;
		}else if(read_bytes == -1){
			close(clnt_sockfd);
			errif(true, "socket read error");
		}
	}
	return 0;
}
