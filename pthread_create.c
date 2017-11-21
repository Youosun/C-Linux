#include "func.h"

void* threadFunc(void* p)
{
	printf("I am thread\n");
}

int main()
{
	pthread_t pthid;
	int ret=pthread_create(&pthid,NULL,threadFunc,NULL);
	if(ret!=0)
	{
		printf("pthread create failed\n");exit(-1);
	}
	sleep(1);
	exit(0);
}
