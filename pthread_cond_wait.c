#include "func.h"

typedef struct {
	pthread_mutex_t mutex;
	pthread_cond_t cond;
}Data;

void* threadFunc(void* p)
{
	Data* t=(Data*)p;
	printf("create thread success\n");
	pthread_mutex_lock(&(t->mutex));
	pthread_cond_wait(&t->cond,&t->mutex);
	pthread_mutex_unlock(&t->mutex);
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

	pthread_join(pthid,NULL);
	exit(0);
}
