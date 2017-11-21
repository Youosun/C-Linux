#ifndef __WORK_QUE__
#define __WORK_QUE__
#include "head.h"

typedef struct tag_node {
	int new_fd;
	struct tag_node *pnext;
}node_t,*pnode_t;

typedef struct {
	pnode_t phead,ptail;
	int capability;
	int size;
	pthread_mutex_t mutex;
}que_t,*pque_t;

#define CAP 1000

void que_init(pque_t);
void que_insert(pque_t,pnode_t);
void que_get(pque_t,pnode_t*);
#endif
