/**************************************
*文件说明:server.c
*作者:cherlene
*创建时间:Thu 18 May 2017 04:55:50 AM PDT
*开发环境:linux 2.6.32-431.el16.x86_64
****************************************/
#include"comm.h"
int main()
{
	int mid = CreatMsgQueue();
	char buf[1024];
	while(1)
	{
		buf[1024] = 0;
		printf("server print#%s\n");
		fflush(stdout);

		ssize_t s = read(0,buf,sizeof(buf)-1);
		if(s>0)
		{
			buf[s-1] = 0;
			SendMsgQueue(mid,SERVER_TYPE,buf);
			printf("send...\n");
		}
		RecvMsgQueue(mid,SERVER_TYPE,buf);
		printf("server print#\n",buf);
	}
	return 0;
}
