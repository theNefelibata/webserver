/*************************************************************************
	> File Name: Channel.h
	> Author: Nefelibata
	> Mail: csehuyi@whu.edu.cn 
	> Created Time: Tue 25 Jan 2022 09:49:54 PM CST
 ************************************************************************/

#pragma once
#include <sys/epoll.h>

class Epoll;

class Channel{
private:
	Epoll *ep;
	int fd;
	uint32_t events;
	uint32_t revents;
	bool inEpoll;

public:
	Channel(Epoll* ep, int fd);
	~Channel();

	void enableReading();

	int getFd();
	uint32_t getEvents();
	uint32_t getRevents();

	bool getInEpoll();
	void setInEpoll();

	//void setEvents();
	void setRevents(uint32_t);
};


