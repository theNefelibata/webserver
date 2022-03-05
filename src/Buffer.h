/*************************************************************************
	> File Name: Buffer.h
	> Author: Nefelibata
	> Mail: csehuyi@whu.edu.cn 
	> Created Time: Sat 05 Mar 2022 08:39:25 PM CST
 ************************************************************************/

#pragma once
#include <string>

class Buffer{
private:
	std::string buf;
public:
	Buffer();
	~Buffer();
	void append(const char* _str, int _size);
	ssize_t size();
	const char* c_str();
	void clear();
	void getline();
};
