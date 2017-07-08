#include<stdio.h>
#include<sys/types.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<stdlib.h>
#include<unistd.h>
int main()
{
	umask(0);
	int fd = open("./txt",O_CREAT|O_RDWR|0666);
	if(fd<0)
	{
		perror("open error!");
		exit(1);
	}
	close(1);
	//int newfd = dup(fd);
	int newfd = dup2(fd,1);
	if(newfd <0)
	{
		perror("dup error!");
		exit(2);
	}
	char buf[1024] = "nice to meet you!";
	printf("%s\n",buf);
	fflush(stdout);
	close(fd);
	return 0;
}
