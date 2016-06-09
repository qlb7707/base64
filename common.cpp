/*================================================================
*   Copyright (C) 2016 All rights reserved.
*   
*   filename     :common.cpp
*   author       :qinlibin
*   create date  :2016/06/09
*   mail         :qin_libin@foxmail.com
*
================================================================*/
using namespace std;
#include "common.h"
#include <sstream>
int str2int(string s)
{
    int num;
    istringstream iss(s);
    iss >> num;
    return num;
}
void generate_reversed_key(string key,vector<int> &reversed)
{
    int sz = key.length();
    for(int i = 0; i < sz; i++)
    {
        reversed[key[i]] = i;
    }
}
