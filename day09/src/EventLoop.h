/*************************************************************************
	> File Name: EventLoop.h
	> Author: Nefelibata
	> Mail: csehuyi@whu.edu.cn 
	> Created Time: Wed 26 Jan 2022 04:22:00 PM CST
 ************************************************************************/

#pragma once
class Epoll;
class Channel;
class EventLoop{
private:
	Epoll* ep;
	bool quit;

public:
	EventLoop();
	~EventLoop();

	void loop();
	void updateChannel(Channel*);
};
