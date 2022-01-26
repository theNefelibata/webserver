/*************************************************************************
	> File Name: Channel.h
	> Author: Nefelibata
	> Mail: csehuyi@whu.edu.cn 
	> Created Time: Tue 25 Jan 2022 09:49:54 PM CST
 ************************************************************************/

#pragma once
#include <sys/epoll.h>
#include<functional>

class EventLoop;

class Channel{
private:
	EventLoop *loop;
	int fd;
	uint32_t events;
	uint32_t revents;
	bool inEpoll;
	std::function<void()> callback;

public:
	Channel(EventLoop* _loop, int _fd);
	~Channel();
	
	void handleEvent();
	void enableReading();

	int getFd();
	uint32_t getEvents();
	uint32_t getRevents();

	bool getInEpoll();
	void setInEpoll();

	//void setEvents();
	void setRevents(uint32_t);
	void setCallback(std::function<void()>);
};


