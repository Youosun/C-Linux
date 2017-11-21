#include "func.h"

void* threadFunc(void* p)
{
	printf("I am a pthread\n");
	char* p1;
	p1=(char*)malloc(20);
	strcpy(p1,"hello world");
	pthread_exit(p1);
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
	
	char* p;
	ret=pthread_join(pthid,(void**)&p);
	if(ret!=0)
	{
		printf("pthread join failed\n");
	}
	printf("I am main thread %s\n",p);

	exit(0);
}


