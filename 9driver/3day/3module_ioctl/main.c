/*************************************************************************
	> File Name: main.c
	> Author: joglee
	> Mail: li15041829350@163.com
	> Created Time: Tue 31 Oct 2017 09:34:02 PM CST
 ************************************************************************/

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <sys/ioctl.h>

#include "cmd.h"

int main(int argc, const char* argv[])
{
    int fd;
    int ret = 0;

    struct node buf;
    struct node temp;

    //mknod  /dev/test c 500 0
    fd = open("/dev/test",O_RDWR);
    if(fd < 0){
        perror("Failed to open.\n");

        return -1;
    }
    else
    {
        printf("open success.\n");
    }
    ret = ioctl(fd,CMD);
    printf("ret:%d\n",ret);
    getchar();

    buf.val = 100;
    buf.ch = 'x';
    ret = ioctl(fd,CMDW,&buf);
    printf("ret:%d\n",ret);
    getchar();

    ret = ioctl(fd,CMDR,&temp);
    printf("ret:%d,val:%d,ch:%c\n",ret,temp.val,temp.ch);

    close(fd);

    return 0;
}

