#include "func.h"

int main(int argc,char* argv[])
{
	if(argc!=3)
	{
		printf("error args\n");exit(-1);
	}
	int sfd;
	sfd=socket(AF_INET,SOCK_STREAM,0);
	if(sfd==-1)
	{
		printf("socket failed\n");exit(-1);
	}
	int ret;
	struct sockaddr_in myaddr;
	memset(&myaddr,0,sizeof(myaddr));
	myaddr.sin_family=AF_INET;
	myaddr.sin_port=htons(atoi(argv[2]));
	myaddr.sin_addr.s_addr=inet_addr(argv[1]);
	ret=connect(sfd,(struct sockaddr*)&myaddr,sizeof(myaddr));
	if(ret==-1)
	{
		printf("connect failed ret=%d\n",ret);exit(-1);
	}
	char buf[64]={0};
	fd_set rdset;
	while(1)
	{
		FD_ZERO(&rdset);
		FD_SET(0,&rdset);
		FD_SET(sfd,&rdset);
		select(sfd+1,&rdset,NULL,NULL,NULL);
		if(FD_ISSET(0,&rdset))
		{
			memset(buf,0,sizeof(buf));
			ret=read(0,buf,sizeof(buf));
			if(ret>0)
			{
				send(sfd,buf,strlen(buf)-1,0);
			}else{
				printf("NO INPUT MESG\n");
			}
		}
		if(FD_ISSET(sfd,&rdset))
		{
			memset(buf,0,sizeof(buf));
			ret=recv(sfd,buf,sizeof(buf),0);
			if(ret>0)
			{
				printf("SERVER-->%s\n",buf);
			}else{
				printf("BYEBYE\n");
				break;
			}
		}
	}
	close(sfd);
	return 0;
}
