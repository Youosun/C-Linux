#include "func.h"

typedef struct {
	pthread_mutex_t mutex;
	pthread_cond_t cond;
}Data;

void* threadFunc(void* p)
{
	Data* t=(Data*)p;
	static short i=0;
	short j;
	pthread_mutex_lock(&(t->mutex));
	printf("create thread success %d\n",i);
	j=i;i++;
	pthread_cond_wait(&t->cond,&t->mutex);
	printf("I am wakeup %d\n",j);
	pthread_mutex_unlock(&t->mutex);
	pthread_exit((void*)0);
}

int main()
{
	Data t;
	pthread_mutex_init(&t.mutex,NULL);
	pthread_cond_init(&t.cond,NULL);

	pthread_t pthid1,pthid2;
	pthread_create(&pthid1,NULL,threadFunc,&t);
	pthread_create(&pthid2,NULL,threadFunc,&t);

//	usleep(50);
	sleep(3);			//发信号时线程创建不一定完成 且不一定阻塞在wait
	int ret;
	ret=pthread_cond_signal(&t.cond);
	if(ret!=0)
	{
	    printf("pthread_cond_signal failed ret=%d\n",ret);
	    return -1;
	}
	ret=pthread_cond_signal(&t.cond);
	printf("send signal success\n");
//	ret=pthread_cond_broadcast(&t.cond);
//	printf("pthread_cond_broadcast ret=%d\n",ret);
	pthread_join(pthid1,NULL);
	pthread_join(pthid2,NULL);
	printf("I am main thread\n");
	exit(0);
}
