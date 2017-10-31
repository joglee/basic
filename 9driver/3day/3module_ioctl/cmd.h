/*************************************************************************
	> File Name: cmd.h
	> Author: joglee
	> Mail: li15041829350@163.com
	> Created Time: Tue 31 Oct 2017 09:26:33 PM CST
 ************************************************************************/

#ifndef _CMD_H
#define _CMD_H
struct node{
    int val;
    char ch;
};

#define CMD     _IO('c',0)
#define CMDR    _IOR('c',1,struct node)
#define CMDW    _IOW('c',2,struct node)

#endif
