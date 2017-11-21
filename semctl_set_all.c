#include "func.h"

int main()
{
	int semid;
	semid=semget(1233,2,IPC_CREAT|0600);
	if(semid==-1)
	{
		perror("semget");exit(-1);
	}
	unsigned short arr[2]={1,3};
	int ret=semctl(semid,0,SETALL,arr);
	if(-1==ret)
	{
		perror("semctl");exit(-1);
	}
	memset(arr,0,sizeof(arr));
	ret=semctl(semid,0,GETALL,arr);
	if(-1==ret)
	{
		perror("semctl-getall");
		exit(-1);
	}
	printf("%d %d\n",arr[0],arr[1]);
	return 0;
}
