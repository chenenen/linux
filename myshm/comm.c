/**************************************
*文件说明:comm.c
*作者:cherlene
*创建时间:Tue 23 May 2017 04:53:24 AM PDT
*开发环境:linux 2.6.32-431.el16.x86_64
****************************************/
#include"comm.h"
int GetShm()
{
	int key = ftok(PATH_NAME,PROJ_ID);
	if(key<0)
	{
		perror("ftok error!");
		return -1;
	}
	int shmid = shmget(key,4096,IPC_CREAT|0666);
	if(shmid<0)
	{
		perror("shmget error!");
		return -1;
	}
	return shmid;
}


//挂接
char* Shmat(int shmid)
{
	return (char*) shmat(shmid,NULL,0);
}

//去关联
int	Shmdt(char* addr)
{
	return shmdt(addr);
}
int DestoryShm(int shmid)
{
	if(shmctl(shmid,IPC_RMID,NULL)<0)
	{
		perror("shmctl error!");
		return -1;
	}
	return 0;
}
