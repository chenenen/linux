#include<stdio.h>
#include<sys/types.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<stdlib.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<string.h>
#include<netinet/in.h>
#include<pthread.h>
static void Usefun(const char* pro)
{
	printf("Usefun %s [local_ip] [local_port]\n",pro);
}

int main(int argc, char* argv[])
{
	if(argc != 3)
	{
		Usefun(argv[0]);
		exit(1);
	}
	int sock = socket(AF_INET,SOCK_DGRAM,0);
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
	char buf[1024];
	//先读后写
	while(1)
	{
		struct sockaddr_in peer;
		socklen_t sz = sizeof(peer);

		ssize_t s = recvfrom(sock,buf,sizeof(buf)-1,0,(struct sockaddr*)&peer,&sz);
		if(s>0)
		{
			buf[s] = 0;
			printf("(%s:%d)#:%s\n",inet_ntoa(peer.sin_addr),ntohs(peer.sin_port),buf);
			sendto(sock,buf,strlen(buf),0,(struct sockaddr*)&peer,sz);
		}
		else if(s==0)
		{
			printf("client close!\n");
		}
		else
		{
			printf("error!");
		}
	//	close(sock);
	}
	//close(sock);
	return 0;
}
