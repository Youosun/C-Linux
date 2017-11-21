#include "func.h"
void* threadFunc(void* p)
{
	while(1);
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
		printf("pthread_cancel failed ret=%d\n",ret);exit(-1);
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
