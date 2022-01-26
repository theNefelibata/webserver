/*************************************************************************
	> File Name: Socket.h
	> Author: Nefelibata
	> Mail: csehuyi@whu.edu.cn 
	> Created Time: Mon 24 Jan 2022 03:37:10 PM CST
 ************************************************************************/

#pragma once

class InetAdress;
class Socket{
	private:
		int fd;
	public:
		Socket();
		Socket(int _fd);
		~Socket();
		
		void bind(InetAdress* addr);
		void listen();
		void setnonblocking();

		int accept(InetAdress* addr);
		int getFd();
};
