/**************************************
*文件说明:mymkfifo.c
*作者:cherlene
*创建时间:Wed 17 May 2017 08:05:53 AM PDT
*开发环境:linux 2.6.32-431.el16.x86_64
****************************************/
#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
int main()
{
	if(mkfifo("/home/cherlene/mymkfifo/my_fifo",S_IFIFO|0666) == -1)
	{
		perror("mkfifo filed!");
		return -1;
	}
	int fd = open("/home/cherlene/mymkfifo/my_fifo",O_RDONLY);
	if(fd<0)
	{
		perror("open filed!");
		return -2;
	}

	return 0;
}
