#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<unistd.h>
#include<string.h>
#include<stdlib.h>
#include<netinet/in.h>
int main()
{
	int sv[2];
	int ret = socketpair(PF_LOCAL,SOCK_STREAM,0,sv);
	if(ret<0)
	{
		perror("socketpair error!");
		exit(1);
	}	
	
	pid_t id = fork();
	if(id<0)
	{
		perror("fork error!");
		exit(2);
	}
	else if(id == 0)
	{
		close(sv[1]);
		while(1)
		{
			//child read
			char buf[1024];
			ssize_t s = read(sv[0],buf,sizeof(buf)-1);
			printf("father->:%s\n",buf);
			sleep(1);
			strcpy(buf,"nice father!");
			write(sv[0],buf,sizeof(buf)-1);
		}
	}
	else
	{
		close(sv[0]);
		while(1)
		{
			//father write
			char buf[1024] = "hello son!";
			write(sv[1],buf,sizeof(buf)-1);
			ssize_t s = read(sv[1],buf,sizeof(buf)-1);
			printf("child->:%s\n",buf);
		}
	}
	return 0;
}
