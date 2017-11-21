#include "func.h"

int main()
{
	int semid;
	semid=semget(IPC_PRIVATE,1,IPC_CREAT|0600);
	if(semid==-1)
	{
		perror("semget");exit(-1);
	}
	int ret=semctl(semid,0,SETVAL,1);
	if(-1==ret)
	{
		perror("semctl");exit(-1);
	}
	return 0;
}
