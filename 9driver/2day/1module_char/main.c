/*************************************************************************
	> File Name: main.c
	> Author: joglee
	> Mail: li15041829350@163.com
	> Created Time: Mon 30 Oct 2017 10:38:32 AM CST
 ************************************************************************/

#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>

int main(int argc, const char *argv[])
{
    int fd;

    fd = open("/dev/test",O_RDWR);
    if(fd < 0)
    {
        perror("Failed to open.\n");
        return -1;
    }else{
        printf("open success.\n");
    }
    getchar();

    close(fd);

    return 0;
}
