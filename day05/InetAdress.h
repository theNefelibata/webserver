/*************************************************************************
	> File Name: InetAdress.h
	> Author: Nefelibata
	> Mail: csehuyi@whu.edu.cn 
	> Created Time: Mon 24 Jan 2022 03:27:20 PM CST
 ************************************************************************/

#pragma once
#include <arpa/inet.h>

class InetAdress{
public:
	struct sockaddr_in addr;
	socklen_t addr_len;
	InetAdress();
	InetAdress(const char* ip, uint16_t	port);
	~InetAdress();
};

