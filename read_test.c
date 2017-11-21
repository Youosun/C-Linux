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
	int semid,ret;
	semid=semget(ASEM_KEY,3,IPC_CREAT|0600);		//定义一个信号量集合包含两个信号量
	if(semid==-1)
	{
		perror("A---semget");exit(-1);
	}
	ret=semctl(semid,0,SETVAL,1);					//对于写操作0  初始化信号量为1
	if(ret==-1)
	{
		perror("semctl--writer");exit(-1);
	}
	ret=semctl(semid,1,SETVAL,0);					//对于读操作1   初始化信号量为0
	if(ret==-1)
	{
		perror("semctl---reader");exit(-1);
	}
	ret=semctl(semid,2,SETVAL,1);	
	if(ret==-1)
	{
		perror("semctl---mutex");exit(-1);
	}

	char buf[MSG_LEN]={0};
	int shmid;
	shmid=shmget(ASHM_KEY,sizeof(Data),IPC_CREAT|0600);
	if(shmid==-1)
	{
		perror("shmget");exit(-1);
	}
	pData p;
	Data dummyp;
	int readLen;
	p=(pData)shmat(shmid,NULL,0);
	if(p==(pData)-1)
	{
		perror("shmat");exit(-1);
	}
	memset(p,0,sizeof(Data));
	while(1)
	{
	//	memset(p,0,sizeof(Data));
	//	memset(&dummyp,0,sizeof(Data));
	//	readLen=read(0,dummyp.mesg,MSG_LEN);
	//	dummyp.flag=1;
	//	dummyp.cnt=readLen-1;
	//	printf("%s",buf);
	//		if(ret<=0)
	//		{
	//			printf("byebye\n");
	//			break;
	//		}
		reserveSem(semid,0);
		reserveSem(semid,2);
	//	memcpy(p,&dummyp,sizeof(Data));
		memset(p->mesg,0,MSG_LEN);
		p->flag=1;
		p->cnt=read(0,p->mesg,MSG_LEN)-1;
		releaseSem(semid,1);
		releaseSem(semid,2);
		printf("%d %d %s",p->flag,p->cnt,p->mesg);
	}
	return 0;
}	
