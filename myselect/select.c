#include<stdio.h>
#include<sys/types.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<unistd.h>
#include<string.h>
static void UseFun(const char* pro)
{
	printf("Usefun:%s [local_ip] [local_port]",pro);
	exit(2);
}
static int CreateSock(const char* ip,int port)
{
	int sock = socket(AF_INET,SOCK_STREAM,0);
	if(sock<0)
	{
		perror("socket error!");
		exit(3);
	}

	int opt = 1;
	setsockopt(sock,SOL_SOCKET,SO_REUSEADDR,&opt,sizeof(opt));
	
	struct sockaddr_in local;
	local.sin_family = AF_INET;
	local.sin_addr.s_addr = inet_addr(ip);
	local.sin_port = htons(port);
	if(bind(sock,(struct sockaddr*)&local,sizeof(local))<0)
	{
		perror("bind error!");
		exit(4);
	}

	if(listen(sock,10)<0)
	{
		perror("listen error!");
		exit(5);
	}
}
int main(int argc,char* argv[])
{
	if(argc != 3)
	{
		UseFun(argv[0]);
		return 1;
	}
	int listen_sock = CreateSock(argv[1],atoi(argv[2]));
	//1、进行设置一些需要的变量：包括maxfd和fd数组
	int fd[1024];
	int sz = sizeof(fd)/sizeof(fd[0]);
	//int maxfd = -1;
	int i = 0;
	for(i = 1; i<sz; i++)
	{
		fd[i] = -1;
	}
	fd[0] = listen_sock;
	struct sockaddr_in client;
	client.sin_family = AF_INET;
	client.sin_port = htons(atoi(argv[2]));
	client.sin_addr.s_addr = inet_addr(argv[1]);
	while(1)
	{
		int maxfd = -1;
		//2、进行select读和timeout参数的设置
		struct timeval time = {3,0};
		fd_set rfd;
		FD_ZERO(&rfd);
		int i = 0;
		for(i = 1; i<sz; i++)
		{
			FD_SET(fd[i],&rfd);
			if(fd[i]>maxfd)
			{
				maxfd = fd[i];
			}
		}

		//3、设置好参数，就进行select I/O多路等待
	//	int ret = select(sz,&rfd,NULL,NULL,&time);
		switch(select(maxfd+1,&rfd,NULL,NULL,&time))
		{
			case -1:
				{
					printf("select error!");
					break;
				}
			case 0:
				{
					printf("timeout...\n");
					break;
				}
				//正确执行并且有就绪时间到达返回
			default:
				{
					int i = 0;
					for(i = 0; i<sz; i++)
					{
						if(i == 0 && FD_ISSET(fd[i],&rfd)){
							//普通的套接字直接读写就可以了，但是监听套接字要进行accept
							struct sockaddr_in client;
							socklen_t len = sizeof(client);
							int newsock = accept(listen_sock,(struct sockaddr*)&client,&len);
							if(newsock<0)
							{
								perror("accept error!");
								continue;
							}
							
							
							int j = 1;
							for(;i<sz;j++)
							{
								if(fd[j] == -1)
									break;
								//数组满了
								else if(j == sz)
								{
									close(newsock);
								}
								else
								{
									fd[j] = newsock;
								}
							}
						}
						else if(i != 0 && FD_ISSET(fd[i],&rfd))
						{
							//此处不是监听套接字，因此就进行正常的读写就可以了
							char buf[1024];
							ssize_t s = read(fd[i],buf,sizeof(buf)-1);
							if(s>0)
							{
								buf[s] =0;
								printf("client#:%s\n",buf);
								write(fd[i],buf,strlen(buf));
							}
							
							else if(s == 0)
							{
								printf("client stop!");
								close(fd[i]);
								fd[i] = -1;
							}
							else
							{
								printf("read error!");
								close(fd[i]);
								fd[i] = -1;
							}

						}
						else
						{
							printf("default!");
						}
					}
				}
					break;
				}
		}	
		return 0;
	}
