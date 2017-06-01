/**************************************
*文件说明:mycond.c
*作者:cherlene
*创建时间:Mon 29 May 2017 11:07:30 PM PDT
*开发环境:linux 2.6.32-431.el16.x86_64
****************************************/
#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<assert.h>
#include<unistd.h>
typedef struct listnode
{
	int _data;
	struct listnode* _next;
}Node,*Node_p,**Node_pp;

Node_p _h = NULL;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
int IsEmpty(Node_p _h)
{
	return (_h->_next == NULL)?1:0;
}

Node_p BuyNode(int data)
{
	Node_p newnode = (Node_p)malloc(sizeof(Node));
	if(newnode)
	{
		newnode->_data = data;
		newnode->_next = NULL;
	}
	return newnode;
}

void InitList(Node_pp _h)
{
	*_h = BuyNode(0);
}

void PushFront(Node_p _h,int data)
{
	assert(_h);
	Node_p _n = BuyNode(data);
	_n->_next = _h->_next;
	_h->_next = _n;
}

void PopFront(Node_p _h,int* outdata)
{
	assert(_h);
	if(!IsEmpty(_h))
	{
		Node_p del = _h->_next;
		_h->_next = del->_next;
		*outdata = del->_data;
		free(del);
	}
}

void DistroyNode(Node_p _h)
{
	assert(_h);
	int data = 0;
	while(!IsEmpty(_h))
	{
		PopFront(_h,&data);
	}
	free(_h);
	_h = NULL;
}

void Print(Node_p _h)
{
	assert(_h);
	Node_p cur = _h->_next;
	while(cur)
	{
		printf("cur->_data->:%d",cur->_data);
		cur = cur->_next;
	}
	printf("\n");
}
//说明：对于条件变量等待有三步：
//1、在该条件变量下，释放掉所有的锁
//2、阻塞等待
//3、通过信号被唤醒,获得锁

void* product(void* arg)
{
	int data = 0;
	while(1)
	{
		data = rand()%100;
		pthread_mutex_lock(&mutex);
		PushFront(_h,data);
		pthread_mutex_unlock(&mutex);
		pthread_cond_signal(&cond);
		printf("productor:%d\n",data);
		sleep(1);
	}
	return NULL;
}

void* consume(void* arg)
{
	int data = 0;
	while(1)
	{
		pthread_mutex_lock(&mutex);
		//如果链表是空的话，说明没有数据，就要一直等待
		while(IsEmpty(_h))
		{
			pthread_cond_wait(&cond,&mutex);
		}
		PopFront(_h,&data);
		pthread_mutex_unlock(&mutex);
		printf("consumer:%d\n",data);
		sleep(1);
	}
	return NULL;
}

void* thread(void* arg)
{
	int data = 0;
	while(1)
	{
		pthread_mutex_lock(&mutex);
		while(IsEmpty(_h))
		{
			pthread_cond_wait(&cond,&mutex);
		}
		PopFront(_h,&data);
		pthread_mutex_unlock(&mutex);
		printf("tid:%d\n",data);
		sleep(2);
	}
}

int main()
{
	InitList(&_h);
	//PushFront(_h,1);
	//PushFront(_h,2);
	//PushFront(_h,3);

	//Print(_h);
	
	pthread_t productor,consumer,tid;
	pthread_create(&productor,NULL,product,NULL);
	pthread_create(&consumer,NULL,consume,NULL);
	pthread_create(&tid,NULL,thread,NULL);

	pthread_join(productor,NULL);
	pthread_join(consumer,NULL);
	pthread_join(tid,NULL);

	DistroyNode(_h);
	pthread_mutex_destroy(&mutex);
	pthread_cond_destroy(&cond);
}
