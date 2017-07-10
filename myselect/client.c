#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>
#include<netinet/in.h>
#include<sys/types.h>
#include<sys/socket.h>
static void Usefun(const char* pro)
{
	printf("Usefun:%s [server_ip] [server_port]",pro);
	exit(2);
}
int main(int argc,char* argv[])
{
	if(argc != 3)
	{
		Usefun(argv[0]);
		return 1;
	}
	int sock = socket(AF_INET,SOCK_STREAM,0);
	if(sock<0)
	{
		perror("sock error!");
		exit(3);
	}

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
	//client先写后读
	while(1)
	{
		printf("please enter#:");
		fflush(stdout);
		//char buf[1024];
		ssize_t s = read(0,buf,sizeof(buf)-1);
		if(s>0)
		{
			buf[s] = 0;
			write(sock,buf,strlen(buf));
			//将标准输出进行重定向
		//	int fd = dup(1);//fd表示标准输出
		//	dup2(sock,1);   //将标准输出重定向到sock
			printf("client#:%s\n",buf);
		//	dup2(fd,1);    //恢复标准输出到fd
			ssize_t s1 = read(sock,buf,sizeof(buf)-1);
			if(s1>0)
			{
				buf[s] = 0;
			}
		}
	}

	return 0;
}

