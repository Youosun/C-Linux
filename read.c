#include "func.h"

int main()
{	
	int fdr=open(FIFO_1,O_RDONLY);
	if(-1==fdr)
	{
		perror("open");
		return -1;
	}
	int fdw=open(FIFO_2,O_WRONLY);
	if(-1==fdw)
	{
		perror("open");
		return -1;
	}
	char buf[MSG_LEN]={0};
	int ret;
	fd_set rset;
	Data readMsg,writeMsg;
	int shmid;
	shmid=shmget(ASHM_KEY,SHM_SIZE_NO*sizeof(Data),IPC_CREAT|0600);
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
	while(1)
	{
		FD_ZERO(&rset);
		FD_SET(0,&rset);
		FD_SET(fdr,&rset);
		ret=select(fdr+1,&rset,NULL,NULL,NULL);
		if(ret>0)
		{
			if(FD_ISSET(0,&rset))
			{
				memset(buf,0,sizeof(buf));
				ret=read(0,buf,sizeof(buf));
				if(ret>0)
				{
					write(fdw,buf,strlen(buf)-1);
				}else{
					printf("byebye\n");
					break;
				}
				memset(&writeMsg,0,sizeof(Data));
				strncpy(writeMsg.mesg,buf,strlen(buf)-1);
				writeMsg.flag=1;
				//send to shm



				printf("%d %s\n",writeMsg.flag,writeMsg.mesg);
			}
			if(FD_ISSET(fdr,&rset))
			{
				memset(buf,0,sizeof(buf));	
				ret=read(fdr,buf,sizeof(buf));
				if(ret>0)
				{
					printf("B:%s\n",buf);
				}else{
					printf("byebye\n");
					break;
				}
				memset(&readMsg,0,sizeof(Data));
				strncpy(readMsg.mesg,buf,strlen(buf)-1);
				readMsg.flag=0;
				//send to shm
				printf("%d %s\n",readMsg.flag,readMsg.mesg);





			}
		}else{
			printf("no fd read\n");
		}
	}
	close(fdw);
	close(fdr);
	return 0;
}	
