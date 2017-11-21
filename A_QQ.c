#include "func.h"

#define FIFO_1 "1.fifo"
#define FIFO_2 "2.fifo"
#define KEY_A 1111
#define KEY_B 2222
#define MSG_LEN 512
#define SHM_LEN 1024

struct data {
	int flag;
	char message[MSG_LEN];
};

int main()
{	
	int fdr,fdw,ret;
	fdr=open(FIFO_1,O_RDONLY);
	if(-1==fdr)
	{
		perror("open fifo1");
		exit(-1);
	}
	fdw=open(FIFO_2,O_WRONLY);
	if(-1==fdw)
	{
		perror("open fifo2");
		exit(-1);
	}
//	struct data readMsg,writeMsg;
	char buf[512]={0};
	fd_set rset;
	while(1)
	{
		FD_ZERO(&rset);
		FD_SET(0,&rset);
		FD_SET(fdr,&rset);
		select(fdr+1,&rset,NULL,NULL,NULL);
		if(FD_ISSET(fdr,&rset))
		{
//			memset(&readMsg,0,sizeof(readMsg));
//			ret=read(fdr,readMsg.message,MSG_LEN);
			memset(buf,0,sizeof(buf));
			ret=read(fdr,buf,sizeof(buf));
			if(ret<0)
			{
				perror("read message");
				return -1;
			}	
	//		readMsg.flag=0;   			//0 表示对端发送的消息
			//上传至shared mem
	//		printf("%d  %s\n",readMsg.flag,readMsg.message);
			printf("%s\n",buf);
		}
		if(FD_ISSET(0,&rset))
		{
			//memset(&writeMsg,0,sizeof(writeMsg));
			memset(buf,0,sizeof(buf));
			ret=read(0,buf,sizeof(buf));
			if(ret<0)
			{
				perror("read STDIN");
				exit(-1);
			}	
			//writeMsg.flag=1;   			//1 表示己方发送的消息
			//发送至shm
			//ret=write(fdw,writeMsg.message,strlen(writeMsg.message)-1);
			ret=write(fdw,buf,strlen(buf)-1);
			if(ret<0)
			{
				perror("write message");exit(-1);
			}
		}
	}
	close(fdw);
	close(fdr);
}
