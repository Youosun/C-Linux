#include "func.h"

static void*
threadFunc(void* arg)
{
	int j;
	printf("New thread started\n");
	for(j=1;;j++)
	{
		printf("Loop %d\n",j);
		sleep(1);
	}
	return NULL;
}

int main()
{
	pthread_t pthid;
	int s;
	void* res;

	s=pthread_create(&pthid,NULL,threadFunc,NULL);
	if(s!=0)
	{
		printf("Create thread failed\n");exit(-1);
	}
	sleep(3);

	s=pthread_cancel(pthid);
	if(s!=0)
	{
		printf("pthread_cancel failed\n");exit(-1);
	}

	s=pthread_join(pthid,&res);
	if(s!=0)
	{
		printf("pthread_join failed\n");exit(-1);
	}

	if(res == PTHREAD_CANCELED)
	{	
		printf("thread was canceled\n");
	}else{
		printf("thread was not canceled\n");
	}

	exit(0);
}
