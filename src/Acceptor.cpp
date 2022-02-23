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
	addr = new InetAdress("127.0.0.1", 8888);
	sock->bind(addr);
	sock->listen();
	sock->setnonblocking();
	acceptChannel = new Channel(loop, sock->getFd());
	std::function<void()> cb = std::bind(&Acceptor::acceptConnection, this);
	acceptChannel->setCallback(cb);
	acceptChannel->enableReading();
}

Acceptor::~Acceptor(){
	delete sock;
	delete addr;
	delete acceptChannel;
}

void Acceptor::acceptConnection(){
	newConnectionCallback(sock);
}

void Acceptor::setNewConnectionCallback(std::function<void(Socket*)> _cb){
	newConnectionCallback = _cb;
}
