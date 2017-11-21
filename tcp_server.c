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
	ret=bind(sfd,(struct sockaddr*)&myaddr,sizeof(myaddr));
	if(ret==-1)
	{
		printf("bind failed\n");exit(-1);
	}
	ret=listen(sfd,10);
	if(ret==-1)
	{
		printf("listen failed\n");exit(-1);
	}
	int new_fd=-1;
	struct sockaddr_in sockclient;
	int len=sizeof(sockclient);
	char buf[64]={0};
	fd_set rdset,tmpset;
	FD_ZERO(&tmpset);
	FD_SET(0,&tmpset);
	FD_SET(sfd,&tmpset);
	while(1)
	{	
		FD_ZERO(&rdset);
		memcpy(&rdset,&tmpset,sizeof(fd_set));
		ret=select(11,&rdset,NULL,NULL,NULL);
		if(FD_ISSET(sfd,&rdset))
		{
			new_fd=accept(sfd,(struct sockaddr*)&sockclient,&len);
			if(new_fd==-1)
			{
				printf("accept failed\n");exit(-1);
			}
			FD_SET(new_fd,&tmpset);
			printf("client port=%d\n",ntohs(sockclient.sin_port));
			printf("client IP=%s\n",inet_ntoa(sockclient.sin_addr));
			printf("client socklen=%d\n",len);
		}
		if(FD_ISSET(0,&rdset))
		{
			memset(buf,0,sizeof(buf));
			ret=read(0,buf,sizeof(buf));
			if(ret>0)
			{
				ret=send(new_fd,buf,strlen(buf)-1,0);
			}else{
				printf("NO INPUT MESG\n");
			}
		}
		if(FD_ISSET(new_fd,&rdset))
		{
			memset(buf,0,sizeof(buf));
			ret=recv(new_fd,buf,sizeof(buf),0);
			if(ret>0)
			{
				printf("CLIENT-->%s\n",buf);
			}else{
				printf("BYEBYE\n");
				close(new_fd);
				FD_CLR(new_fd,&tmpset);
			}
		}
	}
//	while(1)
//	{
//		FD_ZERO(&rdset);
//		FD_SET(0,&rdset);
//		FD_SET(new_fd,&rdset);
//		select(new_fd+1,&rdset,NULL,NULL,NULL);
//		if(FD_ISSET(0,&rdset))
//		{
//			memset(buf,0,sizeof(buf));
//			read(0,buf,sizeof(buf));
//			send(new_fd,buf,strlen(buf)-1,0);
//		}
//		if(FD_ISSET(new_fd,&rdset))
//		{
//			memset(buf,0,sizeof(buf));
//			ret=recv(new_fd,buf,sizeof(buf),0);
//			if(ret>0)
//			{
//				printf("client-->%s\n",buf);
//			}else{
//				printf("byebye\n");
//				break;
//			}
//		}
//	}
	close(sfd);
	exit(0);
}
