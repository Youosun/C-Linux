#include "func.h"

static int val=10;
void* threadFunc(void* p)
{
	long i=(long)p;
	printf("I am thread %ld val=%d\n",i,val);
	if(i==2)
	{
		val=5;
	}
}

int main()
{
	pthread_t pthid;
	int ret=pthread_create(&pthid,NULL,threadFunc,(void*)1);
	if(ret!=0)
	{
		printf("pthread create failed\n");exit(-1);
	}
	pthread_t pthid1;
	ret=pthread_create(&pthid1,NULL,threadFunc,(void*)2);
	if(ret!=0)
	{
		printf("pthread create failed\n");exit(-1);
	}
	sleep(1);
	exit(0);
}
