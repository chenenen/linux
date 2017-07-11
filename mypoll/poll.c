#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<poll.h>
#include<netinet/in.h>
#define SIZE 10
static void UseFun(const char* pro)
{
	printf("Usefun:%s [local_ip] [local_port]",pro);
}
int main(int argc,char* argv[])
{
	if(argc != 3)
	{
		UseFun(argv[0]);
		return 1;
	}
	int sock = socket(AF_INET,SOCK_STREAM,0);
	if(sock<0)
	{
		perror("socket error!");
		exit(2);
	}
	struct sockaddr_in local;
	local.sin_family = AF_INET;
	local.sin_addr.s_addr = inet_addr(argv[1]);
	local.sin_port = htons(atoi(argv[2]));

	if(bind(sock,(struct sockaddr*)&local,sizeof(local))<0)
	{
		perror("bind error!");
		exit(3);
	}

	if(listen(sock,15)<0)
	{
		perror("listen error!");
		exit(4);
	}
	//poll初始化
	struct pollfd pfd[SIZE];
	int i = 0;
	int maxfd = 0;
	for(i = 0; i<SIZE;i++)
	{
		pfd[i].fd = -1;
	}
	pfd[0].fd = sock;
	pfd[0].events = POLLIN;
	
	while(1)
	{
		switch(poll(pfd,maxfd+1,2))
		{
			case -1:
			{
				printf("poll error!");
				break;
			}
			case 0:
			{
				printf("timeout...\n");
				break;
			}
			default:
			{
				int i=0;
				for(i = 0; i<SIZE; i++)
				{
					if((pfd[0].revents&POLLIN) == POLLIN)
					{
						struct sockaddr_in client;
						client.sin_family = AF_INET;
						client.sin_port = htons(atoi(argv[2]));
						client.sin_addr.s_addr = inet_addr(argv[1]);
						socklen_t len = sizeof(client);
						int newsock = accept(sock,(struct sockaddr*)&client,&len);
						if(newsock <0)
						{
							perror("accept error!");
							exit(5);
						}
						//将完成连接的套接字加入到结构体数组中，以便poll的检测
						int j = 1;
						for(;j<SIZE;j++)
						{
							if(pfd[i].fd == -1)
							{
								break;
							}
							else if(pfd[i].fd == 0)
							{
								close(newsock);
							}
							else
							{
								pfd[i].fd = newsock;
								pfd[i].events = POLLIN;
								break;
							}
						}
						if(j>maxfd)
						{
							maxfd = j;
						}
					}
					else if(i != 0 && (pfd[i].revents &POLLIN) != POLLIN)
					{
						//正常的读写
						char buf[1024];
						ssize_t s = read(sock,buf,sizeof(buf)-1);
						if(s>0)
						{
							buf[s] = 0;
							printf("client#:%s\n",buf);
						}
						else if(s==0)
						{
							printf("client close!");
							close(pfd[i].fd);
							pfd[i].fd = -1;
						}
						else
						{
							printf("read error!");
							exit(6);
						}
					}
					else
					{
						printf("default!");
					}
				}
				break;
			}
		}
	}
	return 0;
}


