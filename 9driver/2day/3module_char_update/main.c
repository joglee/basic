#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

#define   N  128

int main(int argc, const char *argv[])
{
	int fd;
	int ret = 0;
	char buf[N] = {};
	char rbuf[N] = {};

	fd = open("/dev/test", O_RDWR);
	if(fd < 0)
	{
		perror("Failed to open");
		return -1;
	}
	else
	{
		printf("open success.\n");
	}

	strcpy(buf, "This is a write test.");
	
	ret = write(fd, buf, strlen(buf));
	printf("ret:%d\n", ret);
	getchar();

	strcpy(buf, "hello world.");
	ret = write(fd, buf, strlen(buf));
	printf("ret:%d\n", ret);

	getchar();

	ret = read(fd, rbuf, 10);
	printf("ret:%d,%s\n", ret, rbuf);
	getchar();

	memset(rbuf, 0, N);
	ret = read(fd, rbuf, 5);
	printf("ret:%d,%s\n", ret, rbuf);
	getchar();

	memset(rbuf, 0, N);
	ret = read(fd, rbuf, N);
	printf("ret:%d,%s\n", ret, rbuf);
	getchar();

	close(fd);

	return 0;
}
