/**************************************
*文件说明:myshm.c
*作者:cherlene
*创建时间:Tue 23 May 2017 04:48:40 AM PDT
*开发环境:linux 2.6.32-431.el16.x86_64
****************************************/
#include"comm.h"
int main()
{
	int shmid = GetShm();
	pid_t id = fork();
	if(id<0)
	{
		perror("fork error!");
		return -1;
	}
	else if(id == 0)
	{
		//先进行挂接
		char* buf = Shmat(shmid);
		int i = 0;
		while(i<4096)
		{
			buf[i++] = 'A';
		}
		buf[4095] = '\0';
		//写入后进行去关联
		Shmdt(buf);
	}
	else
	{
		char* buf = Shmat(shmid);
		sleep(3);
		printf("%s\n",buf);
		Shmdt(buf);
		wait(NULL);
		DestoryShm(shmid);
	}
	return 0;
}
