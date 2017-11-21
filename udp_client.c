#include "func.h"

int main(int argc,char* argv[])
{
	if(argc!=3)
	{
		printf("error args\n");exit(-1);
	}
	int sfd;
	sfd=socket(AF_INET,SOCK_DGRAM,0);
	if(sfd==-1)
	{
		perror("socket");exit(-1);
	}
	struct sockaddr_in ser;
	memset(&ser,0,sizeof(ser));
	ser.sin_family=AF_INET;
	ser.sin_port=htons(atoi(argv[2]));
	ser.sin_addr.s_addr=inet_addr(argv[1]);

	int ret=sendto(sfd,"I am client",11,0,(struct sockaddr*)&ser,sizeof(struct sockaddr));
	if(ret==-1)
	{
		perror("sendto");exit(-1);
	}
	printf("client send success\n");
	struct sockaddr_in cli;
	memset(&cli,0,sizeof(cli));
	char buf[128]={0};
	int len=sizeof(struct sockaddr);
	ret=recvfrom(sfd,buf,sizeof(buf),0,(struct sockaddr*)&ser,&len);
	if(ret==-1)
	{
		perror("recvfrom");exit(-1);
	}
	printf("client recvfrom %s\n",buf);
	close(sfd);
	exit(0);
}
