#include "func.h"
#include <pthread.h>

pthread_mutex_t mutex;

void* salewin1(void* p)
{
	int *t=(int*)p;
	while(1)
	{
		pthread_mutex_lock(&mutex);	
		if(*t>0)
		{
			printf("salewin1 start sale %d\n",*t);
			(*t)--;
			printf("the ticket sale success %d\n",*t);
			pthread_mutex_unlock(&mutex);
			sleep(2);
		}else{
			pthread_mutex_unlock(&mutex);
			printf("the tickets have sold out\n");
			pthread_exit(NULL);
		}
	}
}

void* salewin2(void* p)
{
	int *t=(int*)p;
	while(1)
	{
		pthread_mutex_lock(&mutex);	
		if(*t>0)
		{
			printf("salewin2 start sale %d\n",*t);
			(*t)--;
			printf("the ticket sale success %d\n",*t);
			pthread_mutex_unlock(&mutex);
			sleep(2);
		}else{
			pthread_mutex_unlock(&mutex);
			printf("the tickets have sold out\n");
			pthread_exit(NULL);
		}
	}
}

int main()
{
	pthread_t pthid1,pthid2;
	int ticket=20;
	pthread_mutex_init(&mutex,NULL);
	pthread_create(&pthid1,NULL,salewin1,&ticket);
	pthread_create(&pthid2,NULL,salewin2,&ticket);
	pthread_join(pthid1,NULL);
	pthread_join(pthid2,NULL);
	printf("the final titcket remain:%d\n",ticket);
	return 0;
}

