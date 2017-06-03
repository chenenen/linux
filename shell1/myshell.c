/**************************************
*文件说明:shell.c
*作者:cherlene
*创建时间:Mon 15 May 2017 08:15:04 AM PDT
*开发环境:linux 2.6.32-431.el16.x86_64
****************************************/
#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<stdlib.h>
#include<fcntl.h>
int main()
{
	while(1)
	{
		printf("[cherlene@www ~]#");
		fflush(stdout);
		char buf[1024];
		ssize_t s = read(0,buf,sizeof(buf)-1);
		if(s>0)
		{
			buf[s-1] = 0;
		}
		char* _a[30];
		char* start = buf;
		 _a[0] = buf;
		int i = 1;
		while(*start)
		{
			if(*start == ' ')
			{
				*start = 0;
				start++;
				_a[i++] = start;
			}
			else
			{
				start++;
			}
		}
		_a[i] = NULL;
		//redirection
		if(strcmp(_a[i-2],">")==0)
		{
			pid_t id = fork();
			if(id<0)
			{
				perror("frok failed!");
				return -1;
			}
			else if(id == 0)
			{
				close(1);
				execvp(_a[0],a);
				open(_a[i-1],O_RDWR|0666);
			//	execvp(_a[0],a);
			}
			else
			{
				wait(NULL);
			}
		}
		else
		{
		//normal	
			pid_t id = fork();
			if(id < 0)
			{
				perror("fork error!");
				return -1;
			}
			else if(id == 0)
			{

				execvp(_a[0],_a);
				exit(1);
			}
			else
			{
				wait(NULL);
			}
		}
	}
	return 0;
	
}
