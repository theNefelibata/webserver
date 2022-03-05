/*************************************************************************
	> File Name: EventLoop.cpp
	> Author: Nefelibata
	> Mail: csehuyi@whu.edu.cn 
	> Created Time: Wed 26 Jan 2022 04:24:00 PM CST
 ************************************************************************/

#include "EventLoop.h"
#include "Epoll.h"
#include "Channel.h"
#include <vector>

EventLoop::EventLoop():ep(nullptr), quit(false){
	ep = new Epoll();
}

EventLoop::~EventLoop(){
	delete ep;
}

void EventLoop::loop(){
	while(!quit){
		std::vector<Channel*> chs;
		chs = ep->poll();
		for(auto it = chs.begin(); it != chs.end(); it++){
			(*it)->handleEvent();
		}
	}
}

void EventLoop::updateChannel(Channel* ch){
	ep->updateChannel(ch);
}

