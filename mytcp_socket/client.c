#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<stdlib.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<string.h>
static void Usefun(const char* pro)
{
	printf("sock:%s [server_ip] [server_port]\n",pro);
	exit(2);
}
int main(int argc,char* argv[])
{
	if(argc != 3)
	{
		Usefun(argv[0]);
		exit(1);
	}
	//1、创建套接字
	int sock = socket(AF_INET,SOCK_STREAM,0);
	if(sock<0)
	{
		perror("sock error!");
		exit(3);
	}
	//2、是TCP，因此要进行建立连接
	struct sockaddr_in server;
	server.sin_family = AF_INET;
	server.sin_port = htons(atoi(argv[2]));
	server.sin_addr.s_addr = inet_addr(argv[1]);
	if(connect(sock,(struct sockaddr*)&server,sizeof(server))<0)
	{
		perror("connect error!");
		exit(4);
	}
	char buf[1024];
	while(1)
	{
		printf("please enter#");
		fflush(stdout);
		ssize_t s = read(0,buf,sizeof(buf)-1);
		if(s>0)
		{
			buf[s] = 0;
			write(sock,buf,strlen(buf));
			ssize_t s1 = read(sock,buf,sizeof(buf)-1);
			if(s1>0)
			{
				buf[s1] = 0;
			//	printf("server#: \n");
			}
		}
	}

//	close(sock);
	return 0;
}
