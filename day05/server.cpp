/*************************************************************************
	> File Name: main.cpp
	> Author: Nefelibata
	> Mail: csehuyi@whu.edu.cn 
	> Created Time: Fri 21 Jan 2022 04:11:47 PM CST
 ************************************************************************/
#include <stdio.h>
#include <iostream>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <vector>
#include "utils.h"
#include "Socket.h"
#include "Epoll.h"
#include "InetAdress.h"
#include "Channel.h"

#define READ_BUFFER 1024

void handdleReadEvent(int fd);

int main(){
	Socket *serv_sock = new Socket();
	InetAdress *serv_addr = new InetAdress("127.0.0.1", 8888);
	serv_sock->bind(serv_addr);
	serv_sock->listen();
	Epoll *ep = new Epoll();
	serv_sock->setnonblocking();
	Channel* servChannel = new Channel(ep, serv_sock->getFd());
	servChannel->enableReading();
	//ep->addFd(serv_sock->getFd(), EPOLLIN|EPOLLET);

	while(true){
		std::vector<Channel*> activateChannels = ep->poll();
		int nfds = activateChannels.size();

		for(int i = 0; i < nfds; i++){
			if(activateChannels[i]->getFd() == serv_sock->getFd()){
				InetAdress *clnt_addr = new InetAdress();
				Socket *clnt_sock = new Socket(serv_sock->accept(clnt_addr));

				std::cout<< "new client fd" << clnt_sock->getFd() << "!, IP : " << inet_ntoa(clnt_addr->addr.sin_addr) << " Port: " << ntohs(clnt_addr->addr.sin_port) <<std::endl;
			
				clnt_sock->setnonblocking();
				Channel* clntChannel = new Channel(ep, clnt_sock->getFd());
				clntChannel->enableReading();
				//ep->addFd(clnt_sock->getFd(), EPOLLIN|EPOLLET);
			}else if(activateChannels[i]->getEvents() && EPOLLIN){
				handdleReadEvent(activateChannels[i]->getFd());
			}else{
				std::cout<< "something else happen" << std::endl;
			}
		}
	}
	delete serv_addr;
	delete serv_sock;
	return 0;
}

void handdleReadEvent(int sockfd){
	char buf[READ_BUFFER];
    while(true){    //由于使用非阻塞IO，读取客户端buffer，一次读取buf大小数据，直到全部读取完毕
        bzero(&buf, sizeof(buf));
        ssize_t bytes_read = read(sockfd, buf, sizeof(buf));
        if(bytes_read > 0){
            printf("message from client fd %d: %s\n", sockfd, buf);
            write(sockfd, buf, sizeof(buf));
        } else if(bytes_read == -1 && errno == EINTR){  //客户端正常中断、继续读取
            printf("continue reading");
            continue;
        } else if(bytes_read == -1 && ((errno == EAGAIN) || (errno == EWOULDBLOCK))){//非阻塞IO，这个条件表示数据全部读取完毕
            printf("finish reading once, errno: %d\n", errno);
            break;
        } else if(bytes_read == 0){  //EOF，客户端断开连接
            printf("EOF, client fd %d disconnected\n", sockfd);
            close(sockfd);   //关闭socket会自动将文件描述符从epoll树上移除
            break;
        }
	}
}
