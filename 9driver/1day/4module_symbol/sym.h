/*************************************************************************
	> File Name: sym.h
	> Author: joglee
	> Mail: li15041829350@163.com
	> Created Time: Sun 29 Oct 2017 04:29:37 PM CST
 ************************************************************************/

#ifndef _SYM_H
#define _SYM_H
struct object {
    int val;
    int (*show)(void);
};
#endif
