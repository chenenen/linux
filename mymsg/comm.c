/**************************************
*文件说明:comm.c
*作者:cherlene
*创建时间:Thu 18 May 2017 04:55:35 AM PDT
*开发环境:linux 2.6.32-431.el16.x86_64
****************************************/
#include"comm.h"

static int CommMsgQueue(int flags)
{
	key_t  key = ftok(PATHNAME,PROJ_ID);
	if(key<0)
	{
		perror("ftok failed!");
		return -1;
	}
	int mid = msgget(key,flags);
	if(mid<0)
	{
		perror("msgget failed!");
		return -2;
	}
	return mid;
}

int CreatMsgQueue()
{
	return CommMsgQueue(IPC_CREAT|IPC_EXCL|0666); 
}

int GetMsgQueue()
{
	return CommMsgQueue(IPC_CREAT);
}

int DestroyQueue(int mid)
{
	if(msgctl(mid,IPC_RMID,NULL)<0)
	{
		perror("msgctl failed!");
		return -1;
	}
	return 0;
}

int SendMsgQueue(int mid,int who,char* msg)
{
	struct msgbuf buf;
	buf.mtype = who;
	strcpy(msg,buf.mtext);
	if(msgsnd(mid,(void*)&buf,sizeof(buf.mtext),0)<0)
	{
		perror("msgsnd failed!");
		return -1;
	}
	return 0;
}

int RecvMsgQueue(int mid,int recvType,char* out)
{
	struct msgbuf buf;
	strcpy(out,buf.mtext);
	if(msgrcv(mid,(void*)&buf,sizeof(buf.mtext),recvType,0)<0)
	{
		perror("msgrcv failed!");
		return -1;
	}
//	strcpy(out,buf.mtext);
	return 0;
}
