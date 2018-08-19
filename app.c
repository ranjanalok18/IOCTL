#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>

#include "lib_ioctl.h"
int main()
{
	int fd = -1;
	char buff[40];
	char buff1[40];
	fd = open("/dev/mycdev", O_RDWR);
	if(fd < 0) {
		perror("open failed\n");
		return -1;
	}
	ioctl(fd, IOCTL_READ, buff);
	printf("Data...At USER %s\n", buff);
	strcpy(buff1, "Data for USER");
	ioctl(fd, IOCTL_WRITE, buff1);
//	printf("Data Done \n");
	close(fd);
	return 0;
}

