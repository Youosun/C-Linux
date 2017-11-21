#include "func.h"
void cleanupFunc(void* p)
{
	printf("I am cleanup func\n");
	free(p);
}

void* threadFunc(void* p)
{
	char* sp;
	sp=(char*)malloc(20);
	pthread_cleanup_push(cleanupFunc,sp);
	printf("I am pthreadFunc\n");
	sleep(5);
	pthread_exit((void*)5);
	pthread_cleanup_pop(1);
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
	sleep(3);
	ret=pthread_cancel(pthid);
	if(ret!=0)
	{
		printf("pthread_cancel failed\n");exit(-1);
	}

	int i;
	ret=pthread_join(pthid,(void**)&i);
	if(ret!=0)
	{
		printf("pthread_join failed\n");exit(-1);
	}
	printf("I am main %d\n",i);
	exit(0);
}
