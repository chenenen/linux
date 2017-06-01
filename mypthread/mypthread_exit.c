/**************************************
*文件说明:mypthread_join.c
*作者:cherlene
*创建时间:Wed 24 May 2017 07:38:05 AM PDT
*开发环境:linux 2.6.32-431.el16.x86_64
****************************************/
#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
#include<pthread.h>
void* thread1(void* arg)
{
	printf("thread1...\n");
	return (void*)1;
}
	
void* thread2(void* arg)
{
	printf("thread2...\n");
	pthread_exit((void*)2);
}

void* thread3(void* arg)
{
	while(1)
	{
		printf("pthread3 running...\n");
		sleep(1);
	}
	return NULL;
}

int main()
{
	pthread_t tid;
	void* ret;
	//thread 1:return 
	pthread_create(&tid,NULL,thread1,NULL);
	pthread_join(tid,&ret);
	printf("thread return,thread id: %u return code:%d \n",(unsigned long)tid,(int)ret);

	//thread 2: exit
	pthread_create(&tid,NULL,thread2,NULL);
	pthread_join(tid,&ret);
	printf("thread return,thread id:%u exit code:%d\n",(unsigned long)tid,(int)ret);

	//thread 3:cancel by other
	pthread_create(&tid,NULL,thread3,NULL);
	sleep(4);
	pthread_cancel(tid);
	pthread_join(tid,&ret);
	printf("thread return,thread id:%u cancle code:%d\n",(unsigned long)tid,(int)ret);
	return 0;


}

