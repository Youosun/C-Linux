#include "func.h"
#define N 100000

int main(int argc,char** argv)
{
	int shmid;
	shmid=shmget(IPC_PRIVATE,4096,IPC_CREAT|0600);
	if(shmid==-1)
	{
		perror("shmget");
		return -1;
	}
	int *p;
	p=(int*)shmat(shmid,NULL,0);
	if(p==(int*)-1)
	{
		perror("shmat");
		return -1;
	}
	*p=0;
	*(p+1)=0;
	if(!fork())
	{
		int i;
		while(*(p+1)==0)
		{
			for(i=0;i<N;i++)
			{
				(*p)++;
			}
			*(p+1)=1;
		}
		exit(0);
	}else{
		int i;
		while(*(p+1)==0)
		{
			while(*(p+1)==1)
			{
				for(i=0;i<N;i++)
				{
					(*p)++;
				}
				*(p+1)=2;
			}
		}
		//wait(NULL);
	}
		printf("sum=%d\n",*p);
		exit(0);
}
