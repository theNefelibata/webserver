/*************************************************************************
	> File Name: client.cpp
	> Author: Nefelibata
	> Mail: csehuyi@whu.edu.cn 
	> Created Time: Fri 21 Jan 2022 04:21:11 PM CST
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<iostream>
#include<arpa/inet.h>
#include<cstring>
#include<unistd.h>
#include<sys/socket.h>
#include "utils.h"


using namespace std;

int main(){
	int sockfd = socket(AF_INET, SOCK_STREAM, 0);
	errif(sockfd == -1, "socket create error!");
	struct sockaddr_in serv_addr;
	bzero(&serv_addr, sizeof(serv_addr));

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	serv_addr.sin_port = htons(8888);

	errif(connect(sockfd, (sockaddr*)&serv_addr, sizeof(serv_addr)) == -1, "socket connect error!");
	
	while(true){
		char buf[1024];
		bzero(&buf, sizeof(buf));
		scanf("%s", buf);
		ssize_t write_bytes = write(sockfd, buf, sizeof(buf));
		if(write_bytes == -1){
			printf("socket already disconnected, can't write anymore!'");
			break;
		}
		ssize_t read_bytes = read(sockfd, buf, sizeof(buf));
		if(read_bytes > 0){
			printf("message from server: %s\n", buf);
		}else if(read_bytes == 0){
			printf("server socket disconnected!\n");
		}else if(read_bytes == -1){
			close(sockfd);
			errif(true, "socket read error!\n");
		}
	}
	return 0;
}
