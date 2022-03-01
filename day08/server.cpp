/*************************************************************************
	> File Name: main.cpp
	> Author: Nefelibata
	> Mail: csehuyi@whu.edu.cn 
	> Created Time: Fri 21 Jan 2022 04:11:47 PM CST
 ************************************************************************/

#include "src/EventLoop.h"
#include "src/Server.h"

int main(){
	EventLoop* loop = new EventLoop();
	Server* server = new Server(loop);
	loop->loop();
	return 0;
	
}
