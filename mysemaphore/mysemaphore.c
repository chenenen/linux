/**************************************
*文件说明:mysemaphore.c
*作者:cherlene
*创建时间:Tue 30 May 2017 01:51:23 AM PDT
*开发环境:linux 2.6.32-431.el16.x86_64
****************************************/
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>
#include<semaphore.h>

int buf[30] = {0};
sem_t blank_sem;
sem_t data_sem;

void* product(void* arg)
{
	int i = 0;
	while(1)
	{
		sem_wait(&blank_sem);
		int data = rand()%1000;
		buf[i+1] = data;
		sem_post(&data_sem);
		printf("productor is producting...:%d\n",data);
		i = i%30;
		sleep(1);
	}
}
void* consume(void* arg)
{
	int i = 0;
	while(1)
	{
		sem_wait(&data_sem);
		int data = buf[i+1];
		printf("consumer is comsuming...:%d\n",data);
		sem_post(&blank_sem);
		i = i%30;
		sleep(1);
	}
}


int main()
{
	sem_init(&blank_sem,0,30);
	sem_init(&data_sem,0,0);
	pthread_t productor,consumer;
	pthread_create(&productor,NULL,product,NULL);
	pthread_create(&consumer,NULL,consume,NULL);
	pthread_join(productor,NULL);
	pthread_join(consumer,NULL);
	sem_destroy(&blank_sem);
	sem_destroy(&data_sem);
}
