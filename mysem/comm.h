/**************************************
*文件说明:comm.h
*作者:cherlene
*创建时间:Mon 22 May 2017 05:19:09 AM PDT
*开发环境:linux 2.6.32-431.el16.x86_64
****************************************/
#ifndef _COMM_H_
#define _COMM_H_
#include<stdio.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/sem.h>
#include<string.h>
#include<unistd.h>
#include<stdlib.h>

union Semun{
	int val;
	struct semid_ds *buf;
	unsigned short  *array;
	struct seminfo  *_buf;
};


#define PATH_NAME "."
#define PROJ_ID 0x6666


int CreatSem(int nums);
int GetSem();
int InitSem(int semid,int who);
int Sem_p(int semid);
int Sem_v(int semid);
int DestorySem(int semid);

#endif
