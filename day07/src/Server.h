/*************************************************************************
	> File Name: Server.h
	> Author: Nefelibata
	> Mail: csehuyi@whu.edu.cn 
	> Created Time: Wed 26 Jan 2022 04:35:25 PM CST
 ************************************************************************/

#pragma once

class EventLoop;
class Socket;
class Acceptor;
class Server{
private:
	EventLoop* loop;
	Acceptor* acceptor;

public:
	Server(EventLoop*);
	~Server();

	void handleReadEvent(int);
	void newConnection(Socket *serv_sock);
};
