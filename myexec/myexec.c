/**************************************
 *文件说明:myexec.c
 *作者:cherlene
 *创建时间:Tue 09 May 2017 07:29:49 PM PDT
 *开发环境:linux 2.6.32-431.el16.x86_64
 ****************************************/
#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
int main()
{
	pid_t id = fork();
	char* a[] = {"ls","-a","-l","-n",NULL,};

	//execl
	if(id == 0)
	{
		if(execl("/bin/ls","ls","-a","-l","-n",NULL) == -1)
		{
			perror("execl error!");
			exit(1);
		}
	}

	//execv
	if(id == 0)
	{
		printf("###########execv##########");
		if(execv("/bin/ls",a)<0)
		{
			perror("execv error!");
			exit(1);
		}
	}

	//execlp
	if(id == 0)
	{
		printf("############execlp#########");
		if(execlp("ls","ls","-a","-l","-n",NULL)<0)
		{
			perror("execlp error!");
			exit(1);
		}
	}

	//execvp
	if(id == 0)
	{
		printf("############execvp##########");
		if(execvp("ls",a)<0)
		{
			perror("execvp error!");
			exit(1);
		}
	}

	//execle
	if(id == 0)
	{
		printf("###########execle##########");
		if(execle("/bin/ls","ls","-a","-l","-n",NULL,NULL)<-1)
		{
			perror("execle error!");
			exit(1);
		}
	}
	return EXIT_SUCCESS;
}
