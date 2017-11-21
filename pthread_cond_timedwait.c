#include "func.h"

typedef struct {
	pthread_mutex_t mutex;
	pthread_cond_t cond;
}Data;

void* threadFunc(void* p)
{
	Data* t=(Data*)p;
	printf("I am child thread\n");
	struct timespec abstime;
	time_t tm;
	time(&tm);					//获取当前时间--秒数
	memset(&abstime,0,sizeof(abstime));
	abstime.tv_sec=tm+2;
	int ret;
	pthread_mutex_lock(&(t->mutex));
	ret=pthread_cond_timedwait(&t->cond,&t->mutex,&abstime);
	pthread_mutex_unlock(&t->mutex);
	printf("pthread_cond_timedwait ret=%d\n",ret);
	printf("I am wakeup\n");
	pthread_exit((void*)0);
}

int main()
{
	Data t;
	pthread_mutex_init(&t.mutex,NULL);
	pthread_cond_init(&t.cond,NULL);

	pthread_t pthid;
	pthread_create(&pthid,NULL,threadFunc,&t);

//	usleep(50);
	sleep(3);		//超时  等待线程失败返回110
	int ret;
	ret=pthread_cond_signal(&t.cond);
	if(ret!=0)
	{
		printf("pthread_cond_signal failed ret=%d\n",ret);
		return -1;
	}
	printf("send signal success\n");
	pthread_join(pthid,NULL);
	printf("I am main thread\n");
	exit(0);
}
