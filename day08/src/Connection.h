/*************************************************************************
	> File Name: Connection.h
	> Author: Nefelibata
	> Mail: csehuyi@whu.edu.cn 
	> Created Time: Wed 23 Feb 2022 09:27:08 PM CST
 ************************************************************************/

#pragma once
#include <functional>

class EventLoop;
class Socket;
class Channel;
class Connection{
private:
	EventLoop *loop;
	Socket *sock;
	Channel *channel;
	std::function<void(Socket*)> deleteConnectionCallback;

public:
	Connection(EventLoop *_loop, Socket *_sock);
	~Connection();
	
	void echo(int sockfd);
	void setdeleteConnectionCallback(std::function<void(Socket*)>);
};
