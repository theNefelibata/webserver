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
#include<sys/epoll.h>
#include<fcntl.h>

#define MAX_EVENTS 1024
#define READ_BUFFER 1024

void setnonblocking(int fd){
	fcntl(fd, F_SETFL, fcntl(fd, F_GETFL) | O_NONBLOCK);
}

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

	int epfd = epoll_create1(0);
	errif(epfd == -1, "epoll create error");

	struct epoll_event events[MAX_EVENTS], ev;
	bzero(&events, sizeof(events));
	bzero(&ev, sizeof(ev));

	ev.data.fd = sockfd;
	ev.events = EPOLLIN | EPOLLET;
	setnonblocking(sockfd);
	epoll_ctl(epfd, EPOLL_CTL_ADD, sockfd, &ev);

	while(true){
		int nfds = epoll_wait(epfd, events, MAX_EVENTS, -1);
		errif(nfds == -1, "epoll wait error");

		for(int i = 0; i < nfds; i++){
			if(events[i].data.fd == sockfd){
				struct sockaddr_in clnt_addr;
				bzero(&clnt_addr, sizeof(clnt_addr));
				socklen_t clnt_addr_len = sizeof(clnt_addr);

				int clnt_sockfd = accept(sockfd, reinterpret_cast<sockaddr*>(&clnt_addr), &clnt_addr_len);
				errif(clnt_sockfd == -1, "socket accept error");
				std::cout<< "new client fd" << clnt_sockfd << "!, IP : " << inet_ntoa(clnt_addr.sin_addr) << " Port: " << ntohs(clnt_addr.sin_port) <<std::endl;
				
				bzero(&ev, sizeof(ev));
				ev.data.fd = clnt_sockfd;
				ev.events = EPOLLIN | EPOLLET;

				setnonblocking(clnt_sockfd);
				epoll_ctl(epfd, EPOLL_CTL_ADD, clnt_sockfd, &ev);
			}else if(events[i].events && EPOLLIN){
				char buf[READ_BUFFER];
				while(true){
					bzero(&buf, sizeof(buf));
					ssize_t reads_bytes  = read(events[i].data.fd, buf, sizeof(buf));
					if(reads_bytes > 0){ //非阻塞io，一次读取buffer大小的数据，直到全部读取完毕
						std::cout<< "message from client fd: " << events[i].data.fd << " : " << buf <<std::endl;
						write(events[i].data.fd, buf, sizeof(buf));
					}else if(reads_bytes == -1 && errno == EINTR){  //客户端正常中断 继续读取
						std::cout << "continue reading..." << std::endl;
						continue;
					}else if(reads_bytes == -1 && ((errno == EAGAIN)||(errno == EWOULDBLOCK))){ //表示非阻塞io，数据一次读取完毕
						std::cout << "finish reading once, errno : " << errno << std::endl;
						break;
					}else if(reads_bytes == 0){
						std::cout << "EOF, client fd  " << events[i].data.fd << "disconnected" << std::endl;
						close(events[i].data.fd);
						break;
					}
				}
			}else{
				std::cout<< "something else happen" << std::endl;
			}
		}
	}
	close(sockfd);
	return 0;
}
