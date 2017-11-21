#ifndef __FACTORY_H__
#define __FACTORY_H__
#include "work_que.h"
#include "head.h"

typedef void* (*pfunc)(void*);

typedef struct {
	que_t que;
	pthread_cond_t cond;
	pfunc downfile;
	pthread_t *pth;
	int thread_num;
	short startflag;
}factory,*pfac;

typedef struct {
	int len;
	char buf[1024];
}train,*ptrain;
#define FILENAME "file"
void factory_init(pfac,int,pfunc);
void factory_start(pfac);

void send_data(int);
int send_n(int,char*,int);

#endif
