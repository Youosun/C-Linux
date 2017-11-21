#include "func.h"
void* threadFunc(void* p)
{
	printf("I am pthread\n");
	pthread_exit((void*)5);
}

int main()
{
	pthread_t pthid;
	int ret;
	ret=pthread_create(&pthid,NULL,threadFunc,NULL);
	if(ret!=0)
	{
		printf("pthread_create failed\n");exit(-1);
	}

	ret=pthread_cancel(pthid);
	if(ret!=0)
	{
		printf("pthread_cancel failed\n");exit(-1);
	}
	int r;
	ret=pthread_join(pthid,(void**)&r);
	if(ret!=0)
	{
		printf("pthread_join failed\n");exit(-1);
	}
	printf("I am main %d\n",r);
	exit(0);
}
