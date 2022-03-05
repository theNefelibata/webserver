/*************************************************************************
	> File Name: Acceptor.h
	> Author: Nefelibata
	> Mail: csehuyi@whu.edu.cn 
	> Created Time: Thu 27 Jan 2022 09:22:38 PM CST
 ************************************************************************/

#pragma once
#include <functional>

class EventLoop;
class Socket;
class InetAdress;
class Channel;
class Acceptor{
private:
	EventLoop *loop;
	Socket *sock;
	Channel* acceptChannel;
	std::function<void(Socket*)> newConnectionCallback;

public:
	Acceptor(EventLoop*);
	~Acceptor();
	void acceptConnection();
	void setNewConnectionCallback(std::function<void(Socket*)>);

};
