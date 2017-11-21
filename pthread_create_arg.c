#include "func.h"

void* threadFunc(void* p)
{
	char *p1=(char*)p;
	printf("I am thread buf=%s\n",p1);
}

int main()
{
	pthread_t pthid;
	char buf[15]="hello world";
	int ret=pthread_create(&pthid,NULL,threadFunc,buf);
	if(ret!=0)
	{
		printf("pthread create failed\n");exit(-1);
	}
	sleep(1);
	exit(0);
}
