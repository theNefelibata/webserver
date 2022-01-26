/*************************************************************************
	> File Name: client.cpp
	> Author: Nefelibata
	> Mail: csehuyi@whu.edu.cn 
	> Created Time: Fri 21 Jan 2022 04:21:11 PM CST
 ************************************************************************/

#include<iostream>
#include<arpa/inet.h>
#include<cstring>
#include<sys/socket.h>

using namespace std;

int main(){
	int sockfd = socket(AF_INET, SOCK_STREAM, 0);
	struct sockaddr_in serv_addr;
	bzero(&serv_addr, sizeof(serv_addr));

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	serv_addr.sin_port = htons(8888);

	connect(sockfd, (sockaddr*)&serv_addr, sizeof(serv_addr));
}