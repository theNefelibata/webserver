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
	addr_len = sizeof(addr);
}
InetAdress::~InetAdress(){
};

void InetAdress::setInetAddr(sockaddr_in _addr, socklen_t _addr_len){
	addr = _addr;
	addr_len = _addr_len;
}

sockaddr_in InetAdress::getAddr(){
	return addr;
}
socklen_t InetAdress::getAddr_len(){
	return addr_len;
}
