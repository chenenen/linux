/**************************************
*文件说明:mysem.c
*作者:cherlene
*创建时间:Mon 22 May 2017 05:18:58 AM PDT
*开发环境:linux 2.6.32-431.el16.x86_64
****************************************/
#include"comm.h"
int main()
{
	int semid = CreatSem(1);
	pid_t id = fork();
	InitSem(semid,0);
	if(id<0)
	{
		perror("fork error!");
		return -1;
	}
	else if(id == 0)
	{
		int semid = GetSem();
		while(1)
		{   
			Sem_p(semid);
			printf("A");
			fflush(stdout);
			usleep(12345);
			printf("A");
			usleep(12360);
			fflush(stdout);
			Sem_v(semid);
		}
	}
	else
	{
		while(1)
		{
			Sem_p(semid);
			printf("B");
			fflush(stdout);
			usleep(12000);
			printf("B");
			fflush(stdout);
			usleep(12030);
			Sem_v(semid);
		}
	}
	DestorySem(semid);
	return 0;
}
