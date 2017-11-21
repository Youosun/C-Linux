#include "func.h"

int reserveSem(int semId,int semNum)
{
	struct sembuf sopp;
	memset(&sopp,0,sizeof(sopp));

	sopp.sem_num=semNum;
	sopp.sem_op =-1;
	sopp.sem_flg=SEM_UNDO;

	while(semop(semId,&sopp,1)==-1)
	{
		printf("semopp failed\n");
		return -1;
	}
	return 0;
}

int releaseSem(int semId,int semNum)
{
	struct sembuf sopv;
	memset(&sopv,0,sizeof(sopv));

	sopv.sem_num=semNum;
	sopv.sem_op=1;
	sopv.sem_flg=SEM_UNDO;

	while(semop(semId,&sopv,1)==-1);
	{
		printf("semopv failed\n");
		return -1;
	}
	return 0;
}

int main()
{
	int semid,shmid,ret;
	semid=semget(ASEM_KEY,2,IPC_CREAT|0600);		//定义一个信号量集合包含两个信号量
	if(semid==-1)
	{
		perror("A---semget");exit(-1)
	}
	shmid=shmget(ASHM_KEY,sizeof(Data),IPC_CREAT|0600);
	if(shmid==-1)
	{
		perror("shmget");exit(-1);
	}
	pData p;
	p=(pData)shmat(shmid,NULL,0);
	if(p==(pData)-1)
	{
		perror("shmat");exit(-1);
	}
	Data recv;
	memset(&recv,0,sizeof(recv));
	while(1)
	{
		if(reserveSem(semid,1)==-1)
		{
			printf("reserveSem failed\n");exit(-1);
		}
		recv.flag=p->flag;
		recv.cnt=p->cnt;
		strncpy(recv.mesg,p->mesg,p->cnt);
		if(releaseSem(semid,0)==-1)
		{
			printf("releaseSem failed\n");exit(-1);
		}
		if(recv.flag==1)
		{
			printf("A:");
			puts(recv.mesg);
		}
		if(recv.flag==2)
		{
			printf("B:");
			puts(recv.mesg);
		}
	}
	exit(0);
}
