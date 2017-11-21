#include "func.h"

int main()
{
	int semid;
	semid=semget(1234,1,IPC_CREAT|0600);
	if(semid==-1)
	{
		perror("semget");exit(-1);
	}
	struct semid_ds buf;
	memset(&buf,0,sizeof(buf));
	int ret=semctl(semid,0,IPC_STAT,&buf);
	if(ret==-1)
	{
		perror("semctl_stat");
		exit(-1);
	}
	printf("cuid=%d mode=%o nsems=%ld\n",buf.sem_perm.cuid,buf.sem_perm.mode,buf.sem_nsems);
	buf.sem_nsems=3;
	ret=semctl(semid,0,IPC_SET,&buf);
	if(-1==ret)
	{
		perror("semtcl-ipc-set");exit(-1);
	}
	return 0;
}
