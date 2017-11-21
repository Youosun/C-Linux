#include "func.h"

int main()
{	
	int fdw=open(FIFO_1,O_WRONLY);
	if(-1==fdw)
	{
		perror("open");
		return -1;
	}
	int fdr=open(FIFO_2,O_RDONLY);
	if(-1==fdr)
	{
		perror("open");
		return -1;
	}
	int ret;
	char buf[MSG_LEN]={0};
	struct data readMsg,writeMsg;
	fd_set rset;
	while(1)
	{
		FD_ZERO(&rset);
		FD_SET(0,&rset);
		FD_SET(fdr,&rset);
		ret=select(fdr+1,&rset,NULL,NULL,NULL);
		if(ret>0)
		{
			if(FD_ISSET(fdr,&rset))
			{
				memset(buf,0,sizeof(buf));
				ret=read(fdr,buf,sizeof(buf));
				if(ret>0)
				{
					printf("A:%s\n",buf);
				}else{
					printf("byebye\n");
					break;
				}
				memset(&readMsg,0,sizeof(readMsg));
				strncpy(readMsg.mesg,buf,strlen(buf)-1);
				readMsg.flag=0;
				//send to shm


				printf("A:%d %s\n",readMsg.flag,readMsg.mesg);
			}
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
				memset(&writeMsg,0,sizeof(writeMsg));
				strncpy(writeMsg.mesg,buf,strlen(buf)-1);
				writeMsg.flag=1;
				//send to shm


				printf("%d %s\n",writeMsg.flag,writeMsg.mesg);
			}
		}else{
			printf("no message\n");
		}
	}
	close(fdr);
	close(fdw);
	return 0;
}	
