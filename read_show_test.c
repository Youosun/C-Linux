#include "func.h"

int reserveSem(int semId,int semNum)
{
	struct sembuf sopp;
	memset(&sopp,0,sizeof(sopp));

	sopp.sem_num=semNum;
	sopp.sem_op =-1;
	sopp.sem_flg=SEM_UNDO;

	semop(semId,&sopp,1);
	return 0;
}

int releaseSem(int semId,int semNum)
{
	struct sembuf sopv;
	memset(&sopv,0,sizeof(sopv));

	sopv.sem_num=semNum;
	sopv.sem_op=1;
	sopv.sem_flg=SEM_UNDO;

	semop(semId,&sopv,1);
	return 0;
}

int main()
{
	int semid,shmid,ret;
	semid=semget(ASEM_KEY,3,IPC_CREAT|0600);		//定义一个信号量集合包含两个信号量
	if(semid==-1)
	{
		perror("A---semget");exit(-1);
	}
	shmid=shmget(ASHM_KEY,sizeof(Data),IPC_CREAT|0600);
	if(shmid==-1)
	{
		perror("shmget");exit(-1);
	}
	pData p=(pData)malloc(sizeof(Data));
	p=(pData)shmat(shmid,NULL,0);
	if(p==(pData)-1)
	{
		perror("shmat");exit(-1);
	}
	Data recv;
	while(1)
	{
		memset(&recv,0,sizeof(recv));
		reserveSem(semid,1);
		reserveSem(semid,2);
//		memcpy(&recv,p,sizeof(Data));
		printf("%d %d %s",p->flag,p->cnt,p->mesg);
		releaseSem(semid,0);
		releaseSem(semid,2);
	//	if(recv.flag==1)
	//	{
	//		printf("A:");
	//		puts(recv.mesg);
	//	}
	//	if(recv.flag==2)
	//	{
	//		printf("B:");
	//		puts(recv.mesg);
	//	}
	}
	exit(0);
}
