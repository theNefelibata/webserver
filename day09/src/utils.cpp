/*************************************************************************
	> File Name: utils.cpp
	> Author: Nefelibata
	> Mail: csehuyi@whu.edu.cn 
	> Created Time: Fri 21 Jan 2022 08:40:11 PM CST
 ************************************************************************/

#include "utils.h"
#include <stdio.h>
#include <stdlib.h>

void errif(bool condition, const char *errmsg){
    if(condition){
        perror(errmsg);
        exit(EXIT_FAILURE);
    }
}
