#include "func.h"

void* threadFunc(void* p)
{
	char *str1=(char*)p;
	printf("I am thread string=%s\n",str1);
}

int main()
{
	char *str;
	str=(char*)malloc(15*sizeof(char));
	strcpy(str,"hello world");
	pthread_t pthid;
	int ret=pthread_create(&pthid,NULL,threadFunc,str);
	if(ret!=0)
	{
		printf("pthread create failed\n");exit(-1);
	}
	pthread_t pthid1;
	ret=pthread_create(&pthid1,NULL,threadFunc,str);
	if(ret!=0)
	{
		printf("pthread create failed\n");exit(-1);
	}
	sleep(1);
	exit(0);
}
