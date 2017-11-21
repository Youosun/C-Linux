#include "func.h"

int main(int argc,char* argv[])
{
	if(argc!=3)
	{
		printf("error args\n");
		exit(-1);
	}
	int sfd;
	sfd=socket(AF_INET,SOCK_DGRAM,0);
	if(sfd==-1)
	{
		perror("socket");
		exit(-1);
	}
	struct sockaddr_in ser,cli;
	memset(&ser,0,sizeof(ser));
	ser.sin_family=AF_INET;
	ser.sin_port=htons(atoi(argv[2]));
	ser.sin_addr.s_addr=inet_addr(argv[1]);
	int ret=bind(sfd,(struct sockaddr*)&ser,sizeof(struct sockaddr));
	if(ret==-1)
	{
		perror("bind");exit(-1);
	}
	char buf[128]={0};
	memset(&cli,0,sizeof(cli));
	int len=sizeof(cli);
	ret=recvfrom(sfd,buf,sizeof(buf),0,(struct sockaddr*)&cli,&len);
	printf("%s\n",buf);
	ret=sendto(sfd,"I am server",11,0,(struct sockaddr*)&cli,sizeof(struct sockaddr));
	if(ret<=0)
	{
		printf("sendto failed\n");exit(-1);
	}
	printf("send success\n");
	close(sfd);
	exit(0);
}
