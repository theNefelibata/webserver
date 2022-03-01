/*************************************************************************
	> File Name: Server.h
	> Author: Nefelibata
	> Mail: csehuyi@whu.edu.cn 
	> Created Time: Wed 26 Jan 2022 04:35:25 PM CST
 ************************************************************************/

#pragma once

#include <map>
class EventLoop;
class Socket;
class Acceptor;
class Connection;
class Server{
private:
	EventLoop* loop;
	Acceptor* acceptor;
	std::map<int, Connection*> connections;

public:
	Server(EventLoop*);
	~Server();
	
	void handleReadEvent(int);
	void newConnection(Socket *sock);
	void deleteConnection(Socket *sock);
};
