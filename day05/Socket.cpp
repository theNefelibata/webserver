/*************************************************************************
	> File Name: Socket.cpp
	> Author: Nefelibata
	> Mail: csehuyi@whu.edu.cn 
	> Created Time: Mon 24 Jan 2022 03:40:29 PM CST
 ************************************************************************/


#include "Socket.h"
#include "InetAdress.h"
#include "utils.h"
#include <unistd.h>
#include <sys/socket.h>
#include <fcntl.h>

Socket::Socket():fd(-1){
	fd = socket(AF_INET, SOCK_STREAM, 0);
	errif(fd == -1, "socket create error");
}

Socket::Socket(int _fd):fd(_fd){
	errif(fd == -1, "socket create error");
}
Socket::~Socket(){
	if(fd != -1){
		close(fd);
		fd = -1;
	}
}

void Socket::bind(InetAdress* addr){
	errif(::bind(fd, (sockaddr*)&addr->addr, addr->addr_len) == -1, "socket bind error");
}

void Socket::listen(){
	errif(::listen(fd, SOMAXCONN) == -1, "socket listen error");
}
void Socket::setnonblocking(){
	fcntl(fd, F_SETFL, fcntl(fd, F_GETFL) | O_NONBLOCK);
}

int Socket::accept(InetAdress* addr){
	int clnt_sockfd = ::accept(fd, (sockaddr*)&addr->addr, &addr->addr_len);
	errif(clnt_sockfd == -1, "socket accept error");
	return clnt_sockfd;
}

int Socket::getFd(){
	return fd;
}
