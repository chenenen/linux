/**************************************
*文件说明:myrwlock.c
*作者:cherlene
*创建时间:Wed 31 May 2017 05:55:56 AM PDT
*开发环境:linux 2.6.32-431.el16.x86_64
****************************************/
#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>
pthread_rwlock_t lock;
int ret = 0;
void* write(void* arg)
{
	while(1)
	{
		if(pthread_rwlock_trywrlock(&lock) != 0)
		{
			printf("read is reading...\n");
			sleep(1);
		}
		else
		{
			ret++;
			printf("writer is:%d write:%d\n",pthread_self(),ret);
			sleep(1);
			pthread_rwlock_unlock(&lock);
		}
		sleep(1);
	}
}
void* read(void* arg)
{
	while(1)
	{
		if(pthread_rwlock_tryrdlock(&lock) != 0)
		{
			printf("write is writing...\n");
			sleep(1);
		}
		else
		{
			printf("reader is:%d read:%d\n",pthread_self(),ret);
			pthread_rwlock_unlock(&lock);
		}
		sleep(1);
	}
}

int main()
{
	pthread_rwlock_init(&lock,NULL);
	pthread_t tid;
	int i = 0;
	for(i = 0; i<5; i++)
	{
		pthread_create(&tid,NULL,write,NULL);
	}
	for(i = 0; i<3; i++)
	{
		pthread_create(&tid,NULL,read,NULL);
	}
	pthread_join(tid,NULL);
	return 0;
}
