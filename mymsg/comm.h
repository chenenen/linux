/**************************************
*文件说明:comm.h
*作者:cherlene
*创建时间:Thu 18 May 2017 04:55:16 AM PDT
*开发环境:linux 2.6.32-431.el16.x86_64
****************************************/
#ifndef _COMM_H_
#define _COMM_H_

#include<stdio.h>
#include<sys/types.h>
#include<sys/msg.h>
#include<sys/ipc.h>
#include<string.h>
#include<unistd.h>

#define PATHNAME "."
#define PROJ_ID 0x6666

#define SERVER_TYPE 1
#define CLIENT_TYPE 2

struct msgbuf
{
	long mtype;
	char mtext[1024];
};

int CreatQueue();
int GetMsgQueue();
int DestoryQueue(int mid);
int SendMsgQueue(int mid,int who,char* msg);
int RecvMsgQueue(int mid,int recvTYpe,char* out);


#endif
