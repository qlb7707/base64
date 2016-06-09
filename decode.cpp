/*================================================================
*   Copyright (C) 2016 All rights reserved.
*   
*   filename     :decode.cpp
*   author       :qinlibin
*   create date  :2016/06/09
*   mail         :qin_libin@foxmail.com
*
================================================================*/
//#include "decode.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
using namespace std;
#include "common.h"

string std_key="ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/=";

int do_decode(unsigned char src[],unsigned char dst[],int len, vector<int> &key)
{
    int real_len = 3;
    int equ_cnt = 0;
    unsigned int number = 0;
    if( len != 4)
    {
        cout<<"string len =" <<len<< ", out of range"<<endl;
        return -1;
    }
    for(int i = 0; i< 4; i++)
    {
        if(src[i] == '=')
        {
            src[i] = 0;
            equ_cnt ++;
        }
        else
            src[i] = key[src[i]];

        number += (unsigned int)(src[i] & 0x3f) << (6 *(3-i));
    }
    real_len -= equ_cnt;

    for(int i = 0; i < 3; i++)
    {
        dst[i] = (number >> 8*(2-i)) & 0x000000ff;
    }

    return real_len;
}

void do_file_decode(string filename,int mode,vector<int> &key)
{
    ifstream ifs;
    ofstream ofs;
    unsigned char ori[4] = {0};
    unsigned char decoded[3] = {0};
    int len = 0;
    int real_len = 0;
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
        ofs.open("base64_decode_out.txt",ios::out);
    else
        ofs.open("base64_decode_out.txt",ios::out | ios::binary);
    while(1)
    {
        len = ifs.read((char*)ori,4).gcount();
        if(len <= 0)
            break;
        real_len = do_decode(ori,decoded,len,key);
        ofs.write((char*)decoded,real_len);
        if(len < 4)
            break;
    }
    ifs.close();
    ofs.close();

}


int main(int argc,char *argv[])
{
    string filename = "base64_out.txt";
    string keyfile = "key.txt";
    string key;
    vector<int> reversed_key(128,-1);
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
    generate_reversed_key(key,reversed_key);
    int mode = 0;
    if(argc >= 2)
    {
        filename = argv[1];
    }
    if(argc == 3)
    {
        mode = str2int(argv[2]);
    }
    do_file_decode(filename,mode,reversed_key);
    
}
