/*************************************************************************
	> File Name: Server.cpp
	> Author: Nefelibata
	> Mail: csehuyi@whu.edu.cn 
	> Created Time: Wed 26 Jan 2022 04:38:34 PM CST
 ************************************************************************/

#include "Server.h"
#include "Socket.h"
#include "InetAdress.h"
#include "Acceptor.h"
#include "Channel.h"
#include "Connection.h"
#include <functional>
#include <sys/socket.h>
#include <unistd.h>
#include <string.h>

#define READ_BUFFER 1024

Server::Server(EventLoop* _loop):loop(_loop), acceptor(nullptr){
	acceptor = new Acceptor(loop);
	std::function<void(Socket*)> cb = std::bind(&Server::newConnection, this, std::placeholders::_1);
	acceptor->setNewConnectionCallback(cb);
}

Server::~Server(){
	delete acceptor;
}

void Server::newConnection(Socket *sock){
	Connection *conn = new Connection(loop, sock);
	std::function<void(Socket*)> cb = std::bind(&Server::deleteConnection, this, std::placeholders::_1);
	conn->setdeleteConnectionCallback(cb);
	connections[sock->getFd()] = conn;
}

void Server::deleteConnection(Socket* sock){
	Connection *conn = connections[sock->getFd()];
	connections.erase(sock->getFd());
	delete conn;
}
