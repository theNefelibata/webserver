/*************************************************************************
	> File Name: InetAdress.cpp
	> Author: Nefelibata
	> Mail: csehuyi@whu.edu.cn 
	> Created Time: Mon 24 Jan 2022 03:29:54 PM CST
 ************************************************************************/
#include "InetAdress.h"
#include<string.h>

InetAdress::InetAdress():addr_len(sizeof(addr)){
	bzero(&addr, addr_len);
}

InetAdress::InetAdress(const char* ip, uint16_t port):addr_len(sizeof(addr)){
	bzero(&addr, addr_len);
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = inet_addr(ip);
	addr.sin_port = htons(port);
}
InetAdress::~InetAdress(){
};

