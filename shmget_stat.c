#include "func.h"

int main(int argc,char** argv)
{
	int shmid;
	shmid=shmget((key_t)1234,4096,IPC_CREAT|0600);
	if(shmid==-1)
	{
		perror("shmget");
		return -1;
	}
	struct shmid_ds buf;
	memset(&buf,0,sizeof(buf));
	int ret=shmctl(shmid,IPC_STAT,&buf);
	if(ret==-1)
	{
		perror("shmctl");
		return -1;
	}
	printf("cuid=%d uid=%d mode=%o size=%ld cpid=%d natt=%ld\n",buf.shm_perm.cuid,buf.shm_perm.uid,buf.shm_perm.mode,buf.shm_segsz,buf.shm_cpid,buf.shm_nattch);
	printf("%d\n",ret);
	return 0;
}
