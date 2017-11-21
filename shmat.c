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
	return 0;
}
