/*================================================================
*   Copyright (C) 2016 All rights reserved.
*   
*   filename     :common.h
*   author       :qinlibin
*   create date  :2016/06/08
*   mail         :qin_libin@foxmail.com
*
================================================================*/
#ifndef _COMMON_H
#define _COMMON_H
#include<iostream>
#include<vector>
extern string std_key;
int str2int(string s);
void generate_reversed_key(string key,vector<int> &reversed);
#endif //COMMON_H
