/*************************************************************************
	> File Name: Epoll.h
	> Author: Nefelibata
	> Mail: csehuyi@whu.edu.cn 
	> Created Time: Mon 24 Jan 2022 03:55:49 PM CST
 ************************************************************************/

#pragma once
#include <sys/epoll.h>
#include <vector>

class Epoll{
	private:
		int epfd;
		struct epoll_event *events;
	public:
		Epoll();
		~Epoll();

		void addFd(int fd, uint32_t op);
		std::vector<epoll_event> poll(int timeout = -1);
};
