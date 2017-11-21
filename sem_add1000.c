#include "func.h"

#define N 10000000

int main(int argc,char* argv[])
{
	int semid;
	semid=semget(IPC_PRIVATE,1,IPC_CREAT|0600);		//创建私有信号量  信号量集合个数为1
	if(semid==-1)
	{
		perror("semget");exit(-1);
	}
	int ret=semctl(semid,0,SETVAL,1);				//SETVAL或SETALL 操作初始化集合中的信号量（只有一个进程需要完成这个任务）
	if(ret==-1)
	{
		perror("semctl");exit(-1);
	}
	int shmid;
	shmid=shmget(IPC_PRIVATE,4096,IPC_CREAT|0600);	
	if(shmid==-1)
	{
		perror("shmget");exit(-1);
	}
	int *p;
	p=(int*)shmat(shmid,NULL,0);			
	if(p==(int*)-1)
	{
		perror("shmat");exit(-1);
	}
	*p=0;
	int i;
	struct sembuf sopv,sopp;						//初始化P/V操作
	memset(&sopv,0,sizeof(sopv));
	memset(&sopp,0,sizeof(sopp));
	sopp.sem_num=0;									//P操作
	sopp.sem_op=-1;
	sopp.sem_flg=SEM_UNDO;

	sopv.sem_num=0;									//V操作
	sopv.sem_op=1;
	sopv.sem_flg=SEM_UNDO;

	if(!fork())
	{
		for(i=0;i<N;i++)
		{
			semop(semid,&sopp,1);					//使用临界区前P操作   (加锁)
			*p=*p+1;
			semop(semid,&sopv,1);					//使用临界区后V操作   (去锁)
		}
		exit(0);
	}else{
		for(i=0;i<N;i++)
		{
			semop(semid,&sopp,1);
			*p=*p+1;
			semop(semid,&sopv,1);
		}
		wait(NULL);
		printf("the value is %d\n",*p);
		exit(0);
	}
}
