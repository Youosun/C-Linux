#include "func.h"

int main(int argc,char** argv)
{
	int shmid;
	shmid=shmget(IPC_PRIVATE,4096,IPC_CREAT|0600);
	if(shmid==-1)
	{
		perror("shmget");
		return -1;
	}
	char *p;
	p=(char*)shmat(shmid,NULL,0);
	if(p==(char*)-1)
	{
		perror("shmat");
		return -1;
	}
	if(!fork())
	{
		printf("I am child,%p,%s\n",p,p);
		while(1);
		exit(0);
	}else{
		strcpy(p,"hello world");
		printf("I am parent,%p,%s\n",p,p);
		wait(NULL);
		exit(0);
	}
}
