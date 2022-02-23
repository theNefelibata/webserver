/*************************************************************************
	> File Name: Channel.cpp
	> Author: Nefelibata
	> Mail: csehuyi@whu.edu.cn 
	> Created Time: Tue 25 Jan 2022 09:55:03 PM CST
 ************************************************************************/

#include "EventLoop.h"
#include "Channel.h"
#include <functional>

Channel::Channel(EventLoop* _loop, int _fd):loop(_loop), fd(_fd), events(0), revents(0), inEpoll(false){}

Channel::~Channel(){}

void Channel::handleEvent(){
	callback();
}

void Channel::enableReading(){
	events = EPOLLIN | EPOLLET;
	loop->updateChannel(this);
}

int Channel::getFd(){
	return fd;
}

uint32_t Channel::getEvents(){
    return events;
}
uint32_t Channel::getRevents(){
    return revents;
}

bool Channel::getInEpoll(){
    return inEpoll;
}

void Channel::setInEpoll(){
    inEpoll = true;
}

// void Channel::setEvents(uint32_t _ev){
//     events = _ev;
// }

void Channel::setRevents(uint32_t _ev){
    revents = _ev;
}

void Channel::setCallback(std::function<void()> _cb){
	callback = _cb;
}
