/**************************************
*文件说明:comm.c
*作者:cherlene
*创建时间:Mon 22 May 2017 05:19:17 AM PDT
*开发环境:linux 2.6.32-431.el16.x86_64
****************************************/
#include"comm.h"
static int CommSem(int nums, int flags)
{
	int key = ftok(PATH_NAME,PROJ_ID);
	if(key<0){
		perror("ftok error!");
		return -1;
	}
	int semid = semget(key,nums,flags);
	if(semid<0)
	{
		perror("semget error!");
		return -2;
	}
	return semid;
}
int CreatSem(int nums)
{
	return CommSem(nums,IPC_CREAT|IPC_EXCL|0666);
}

int GetSem()
{
	return CommSem(0,IPC_CREAT);
}	

int InitSem(int semid,int who)
{
	union Semun semun;
	semun.val = 1;
	if(semctl(semid,who,SETVAL,semun)<0)
	{
		perror("semctl error!");
		return -1;
	}
	return 0;
}

static int SemOP(int semid,int op,int who)
{
	struct sembuf _sembuf[1];
	_sembuf[0].sem_op = op;
	_sembuf[0].sem_num = who;
	int ret = semop(semid,_sembuf,1);
	if(ret<0)
	{
		perror("semop error!");
		return -1;
	}
	return ret;
}

int Sem_p(int semid)
{
	return SemOP(semid,-1,0);
}


int Sem_v(int semid)
{
	return SemOP(semid,1,0);
}

int DestorySem(int semid)
{
	if(semctl(semid,0,IPC_RMID,NULL)<0)
	{
		perror("semctl error!");
		return -1;
	}
	return 0;
}
