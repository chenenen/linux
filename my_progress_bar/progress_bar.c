/**************************************
*文件说明:progress_bar.c
*作者:cherlene
*创建时间:Fri 21 Apr 2017 08:17:08 AM PDT
*开发环境:linux 2.6.32-431.el16.x86_64
****************************************/
#include<stdio.h>
#include<unistd.h>
int main()
{
	char a[101] = {0};
	const char* str = "|/-\\";
	int i = 0;
	while(i<=100)
	{
		a[i] = '$';
		printf("[%-50s] %d%% [%c]\r",a,i,str[i%4]);
		++i;
		fflush(stdout);
		usleep(100000);
	}
	return 0;
}

							   
