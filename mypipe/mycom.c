/**************************************
*文件说明:mycom.c
*作者:cherlene
*创建时间:Tue 16 May 2017 04:03:31 AM PDT
*开发环境:linux 2.6.32-431.el16.x86_64
****************************************/
#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<sys/types.h>
#include<sys/wait.h>
int main()
{
	int	fd[2];
	char buf[1024];
	int status = -1;
	if(pipe(fd) == -1)
	{
		perror("pipe error!");
		return -1;
	}
	else
	{
		pid_t id = fork();
		if(id < 0)
		{
			perror("fork error!");
			return -2;
		}
		else if(id == 0)
		{
			//child write
			//int i= 0;
			while(1)
			{
				close(1);
				
				printf("child write...\n");
				write(fd[1],"hello nice to meet you!",25);
			}
				sleep(2);
			
		}
		else
		{
			//father read
			while(1)
			{
			//	close(0);
		
				ssize_t s = read(fd[0],buf,sizeof(buf)-1);
				if(s>0)
				{
					buf[s-1] = 0;
				}
				//printf("%d\n",s);
				printf("%d\n",WIFEXITED(status));
			}
//			printf("%d\n",WIFEXITED(status));
		}
	}
	return 0;
}
