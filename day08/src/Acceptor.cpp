/*************************************************************************
	> File Name: Acceptor.cpp
	> Author: Nefelibata
	> Mail: csehuyi@whu.edu.cn 
	> Created Time: Thu 27 Jan 2022 09:35:02 PM CST
 ************************************************************************/

#include "Acceptor.h"
#include "Socket.h"
#include "InetAdress.h"
#include "Channel.h"
#include "Server.h"
#include <functional>

Acceptor::Acceptor(EventLoop* _loop):loop(_loop){
	sock  = new Socket();
	InetAdress *addr = new InetAdress("127.0.0.1", 8888);
	sock->bind(addr);
	sock->listen();
	sock->setnonblocking();
	acceptChannel = new Channel(loop, sock->getFd());
	std::function<void()> cb = std::bind(&Acceptor::acceptConnection, this);
	acceptChannel->setCallback(cb);
	acceptChannel->enableReading();
	delete addr;
}

Acceptor::~Acceptor(){
	delete sock;
	delete acceptChannel;
}

void Acceptor::acceptConnection(){
    InetAdress *clnt_addr = new InetAdress();      
    Socket *clnt_sock = new Socket(sock->accept(clnt_addr));      
    printf("new client fd %d! IP: %s Port: %d\n", clnt_sock->getFd(), inet_ntoa(clnt_addr->getAddr().sin_addr), ntohs(clnt_addr->getAddr().sin_port));
    clnt_sock->setnonblocking();
    newConnectionCallback(clnt_sock);
    delete clnt_addr;
}

void Acceptor::setNewConnectionCallback(std::function<void(Socket*)> _cb){
	newConnectionCallback = _cb;
}
