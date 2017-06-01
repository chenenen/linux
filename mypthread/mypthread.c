/**************************************
*文件说明:mypthread.c
*作者:cherlene
*创建时间:Wed 24 May 2017 06:03:07 AM PDT
*开发环境:linux 2.6.32-431.el16.x86_64
****************************************/
#include<stdio.h>
#include<pthread.h>
#include<unistd.h>
#include<string.h>
#include<sys/wait.h>

int g_val = 0;
void* Thread_run(void* arg)
{
	while(1)
	{
		g_val++;
		printf("new thread-> pid: %d, tid: %u\n",getpid(),pthread_self());
		sleep(1);
	}
	return (void*)0;
//	exit(2);
}
int main()
{
	pthread_t tid;
	int ret = pthread_create(&tid,NULL,Thread_run,NULL);	
	if(ret!=0)
	{
		printf("create pthread_create error!:%s\n",strerror(ret));
	}
	while(1)
	{
		printf("main thread-> pid: %d, g_val: %d, tid: %u\n",getpid(),g_val,pthread_self());
		sleep(1);
	}


//	void* pret;
//	int cur = pthread_join(tid,&pret);
//	//不为0的时候，会返回错误码
//	if(cur<0)
//	{
//		printf("pthread_join error! error: %d errstring: %s thread code: %d\n",cur,strerror(cur),(int)cur);
//	}
//	return 0;
}
