/**************************************
*文件说明:mymutex.c
*作者:cherlene
*创建时间:Sun 28 May 2017 07:52:53 AM PDT
*开发环境:linux 2.6.32-431.el16.x86_64
****************************************/
#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>
#include<unistd.h>
int g_val = 0;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
void* thread(void* arg)
{
	int i = 0;
	while(i<5000)
	{
		pthread_mutex_lock(&mutex);
		int temp = g_val;
	//	g_val = temp+1;
		printf("new thread->:  pid:%d  tid:%d  g_val:%d\n",getpid(),pthread_self(),g_val);
		g_val = temp+1;
		i++;
		pthread_mutex_unlock(&mutex);
	}
	return NULL;
}

int main()
{
	pthread_t tid1;
	pthread_t tid2;
	pthread_create(&tid1,NULL,thread,NULL);
	pthread_create(&tid2,NULL,thread,NULL);
	void* ret;
	pthread_join(tid1,&ret);
	pthread_join(tid2,&ret);
	printf("g_val:%d\n",g_val);
	pthread_mutex_destroy(&mutex);
	return 0;
}
