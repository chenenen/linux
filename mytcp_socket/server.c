#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<stdlib.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<string.h>
#include<netinet/in.h>
#include<pthread.h>
///server  127.0.0.1 8082
static void Usefun(char* proc)
{
	//服务器自己的IP和端口号
	printf("sock:%s [local_ip] [local_port]\n",proc);
	exit(2);
}
static int CreatSock(const char* ip,int port)
{
	//1、创建套接字
	int sock = socket(AF_INET,SOCK_STREAM,0);
	if(sock<0)
	{
		perror("socket error!");
		exit(3);
	}
	
	//2、绑定
	struct sockaddr_in local;
	local.sin_family = AF_INET;
	local.sin_port = htons(port);
	local.sin_addr.s_addr = inet_addr(ip);

	if(bind(sock,(struct sockaddr*)&local,sizeof(local))<0)
	{
		perror("bind error!");
		exit(4);
	}
	if(listen(sock,10)<0)
	{
		perror("listen error!");
	}

	return sock;
}
void* Handle(void* arg)
{
	printf("thread->:%d\n",pthread_self());
	int newsock = (int)arg;
	while(1)
	{
		char buf[1024];
		ssize_t s = read(newsock,buf,sizeof(buf)-1);
		if(s>0)
		{
			buf[s] = 0;
			printf("client#:%s\n",buf);
			write(newsock,buf,strlen(buf));
		}
		else
		{
			printf("read...\n");
			break;
		}
	}
}
int main(int argc,char* argv[])
{

	if(argc != 3)
	{
		Usefun(argv[0]);
		exit(1);
		
	}
	
	 //3、监听套接字  
	int listen_sock = CreatSock(argv[1],atoi(argv[2]));
	//struct sockaddr_in cli;
	//cli.sin_family = AF_INET;
	//cli.sin_port = htons(atoi(argv[2]));
	//cli.sin_addr.s_addr = inet_addr(argv[1]);
	while(1)
	{	
		//4、accept
		struct sockaddr_in client;
		socklen_t sz = sizeof(client);
		int newsock = accept(listen_sock,(struct sockaddr*)&client,&sz);
		if(newsock<0)
		{
			perror("accept error!");
			exit(5);
		}

		printf("get newsock %s:%d\n",inet_ntoa(client.sin_addr),ntohs(client.sin_port));
		pthread_t tid;
		pthread_create(&tid,NULL,Handle,(void*)newsock);
		pthread_detach(tid);	
//		pid_t id = fork();
//		//fork失败说明连接过多，直接将其关闭
//		if(fork<0)
//		{
//			close(newsock);
//		}
//		else if(id == 0)//child
//		{
//			if(fork()>0)
//			{
//				exit(7);
//			}
//			//先读后写
//			while(1)
//			{
//				char buf[1024];
//				ssize_t s = read(newsock,buf,sizeof(buf)-1);
//				if(s>0)
//				{
//					buf[s] = 0;
//					printf("client#:%s",buf);
//					write(newsock,buf,strlen(buf));
//				}
//				else if(s==0)
//				{
//					printf("client close!\n");
//					break;
//				}
//				else
//				{
//					perror("RDWR error!");
//					exit(6);
//				}
//			}
//		}
//		else//father--accept
//		{
//			//对于父进程来说什么都不干，此时子进程变成僵尸进程
//			//对于父进程来说一定要关闭套接字描述符，不然系统中的会越来越少
//			//而子进程没关系
//			close(newsock);
//		}
//
	//	close(newsock);
	}
	return 0;
}
