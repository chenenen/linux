#include<stdio.h>
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
	printf("Usefun %s [remote_ip] [remote_port]\n",pro);
}
int main(int argc,char* argv[])
{
	if(argc != 3)
	{
		Usefun(argv[0]);
		exit(1);
	}
	int sock = socket(AF_INET,SOCK_DGRAM,0);
	if(sock<0)
	{
		perror("sock error!");
		exit(2);
	}	

	struct sockaddr_in peer;
	peer.sin_family = AF_INET;
	peer.sin_addr.s_addr = inet_addr(argv[1]);
	peer.sin_port = htons(atoi(argv[2]));
	char buf[1024];
	while(1)
	{
		printf("please enter#:");
		fflush(stdout);
		//struct sockaddr_in peer;
		socklen_t sz= sizeof(peer);
		//ssize_t s = recvfrom(0,buf,sizeof(buf)-1,0,(struct sockaddr*)&peer,&sz);
		ssize_t s = read(0,buf,sizeof(buf)-1);
		if(s>0)
		{
			buf[s-1] = 0;
			sendto(sock,buf,strlen(buf),0,(struct sockaddr*)&peer,sz);
		}

		struct sockaddr_in loc;
		socklen_t t = sizeof(struct sockaddr);
		 s = recvfrom(sock,buf,strlen(buf),0,(struct sockaddr*)&loc,&t);
		if(s>0)
		{
			buf[s] = 0;
			printf("server-->client#:%s\n",inet_ntoa(peer.sin_addr),ntohs(peer.sin_port),buf);
		}
	}
	close(sock);
	return 0;

}

