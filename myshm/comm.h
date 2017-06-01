/**************************************
*文件说明:comm.h
*作者:cherlene
*创建时间:Tue 23 May 2017 04:50:43 AM PDT
*开发环境:linux 2.6.32-431.el16.x86_64
****************************************/
#ifndef _COMM_H_
#define _COMM_H_
#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<sys/ipc.h>
#include<sys/types.h>
#include<sys/shm.h>
#include<sys/wait.h>

#define PATH_NAME "."
#define PROJ_ID 0x6666

int GetShm();
char* Shmat(int shmid);
int Shmdt(char* addr);
int DestoryShm(int shmid);



#endif
