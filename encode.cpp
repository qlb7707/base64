/*================================================================
*   Copyright (C) 2016 All rights reserved.
*   
*   filename     :encode.cpp
*   author       :qinlibin
*   create date  :2016/06/08
*   mail         :qin_libin@foxmail.com
*
================================================================*/
//#include "encode.h"
#include<iostream>
#include<fstream>
#include<sstream>
#include<vector>
using namespace std;
#include"common.h"
string std_key="ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/=";
void test_file_read()
{
    string filename = "test.txt";
    ifstream ifs;
    ifs.open(filename.c_str(),ios::in);
    char tmp[3]={0};
    int i = 0;
    int len = 0;
    while(1)
    {
        len = ifs.read(tmp,3).gcount();
        if(len <= 0)
            break;
        cout<<tmp<<"i="<<i<<endl;
        i++;
        if(len < 3)
            break;
    }
    ifs.close();
}


int do_encode(unsigned char src[],unsigned char dst[], int len, string key)
{
    unsigned int number = 0;
    if(len <= 0 || len > 3)
    {
        cout<<"string len =" <<len<< ", out of range"<<endl;
        return -1;
    }
    //pading
    if(len == 1)
    {
        src[1] = 0;
        src[2] = 0;
    }
    else if(len == 2)
    {
        src[1] = 0;
    }
    for(int i = 0;i < 3;i++)
    {
        number += ( (unsigned int)(src[i]))<<(8*(2-i));
    }
    for(int i = 0; i < 4; i++)
    {
        dst[i] = key[(number >> ((3-i)*6)) & 0x0000003f];
    }

    if(len == 1)
    {
        dst[2] = key[64];
        dst[3] = key[64];
    }
    else if(len == 2)
    {
        dst[3] = key[64];
    }

    return 0;
}

void do_file_encode(string filename, int mode, string key)
{
    ifstream ifs;
    ofstream ofs;
    unsigned char ori[3] = {0};
    unsigned char encoded[4] = {0};
    int len = 0;
    if(mode != 0 && mode != 1)
    {
        cout<<"mode "<<mode<<" not supported!"<<endl;
        return;
    }
    if(!mode)
        ifs.open(filename.c_str(),ios::in);
    else
        ifs.open(filename.c_str(),ios::in | ios::binary);
    if(!ifs)
    {
        cout<<"file:"<<filename<<" open failed!"<<endl;
        return;
    }
    if(!mode)
        ofs.open("base64_out.txt",ios::out);
    else
        ofs.open("base64_out.txt",ios::out | ios::binary);
    while(1)
    {
        len = ifs.read((char*)ori,3).gcount();
        if(len <= 0)
            break;
        do_encode(ori,encoded,len,key);
        ofs.write((char*)encoded,4);
        if(len < 3)
            break;
    }
    ifs.close();
    ofs.close();
}

int main(int argc,char* argv[])
{
    string filename = "test.txt";
    string keyfile = "key.txt";
    string key;
    ifstream kfs;
    kfs.open(keyfile.c_str(),ios::in);
    if(kfs)
    {
       kfs>>key;
       if(key.length() != 65 && key.length() != 64)
       {
           cout<<"Invalid Key! Use standard key instead"<<endl;
           key = std_key;
       }
       else if(key.length() == 64)
       {
           key += "=";
       }
    }
    else
    {
        key = std_key;
    }
    int mode = 0;           // 0 --> txt, 1 --> binary
    if(argc >= 2)
    {
        filename = argv[1];
    }
    if(argc == 3)
    {
        mode = str2int(argv[2]);
    }
    do_file_encode(filename,mode,key);
    return 0;
}
