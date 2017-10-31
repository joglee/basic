/*************************************************************************
	> File Name: main.c
	> Author: joglee
	> Mail: li15041829350@163.com
	> Created Time: Mon 30 Oct 2017 02:04:30 PM CST
 ************************************************************************/

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

#define N 128

int main(int argc, const char *argv[])
{
    int fd;
    int ret = 0;
    char buf[N] = {};
    char rbuf[N] = {};


    fd = open("/dev/test",O_RDWR);
    if(fd < 0)
    {
        perror("Failed to open.\n");
        return -1;
    } 
    else
    {
        printf("open success.\n");
    }

    strcpy(buf, "This is a write test.\n");

    ret = write(fd, buf, strlen(buf) + 1);
    printf("ret:%d\n",ret);

    getchar();

    ret = read(fd,rbuf,N);
    printf("ret:%d,%s\n",ret,rbuf);

    close(fd);

    return 0;
}

