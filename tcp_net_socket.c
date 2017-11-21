#include "tcp_net_socket.h"

int tcp_init(const char* ip,int port)
{
	int sfd=socket(AF_INET,SOCK_STREAM,0);
	if(sfd==-1)
	{
		perror("socket");exit(-1);
	}
	struct sockaddr_in serveraddr;
	memset(&serveraddr,0,sizeof(serveraddr));
	serveraddr.sin_family=AF_INET;
	serveraddr.sin_port=htons(port);
	serveraddr.sin_addr.s_addr=inet_addr(ip);
	if(bind(sfd,(struct sockaddr*)&serveraddr,sizeof(struct sockaddr))==-1)
	{
		perror("bind");close(sfd);exit(-1);
	}
	if(listen(sfd,10)==-1)
	{
		perror("listen");close(sfd);exit(-1);
	}
	return sfd;
}

int tcp_accept(int sfd)
{
	int new_fd;
	struct sockaddr_in clientaddr;
	memset(&clientaddr,0,sizeof(clientaddr));
	int addrlen=sizeof(struct sockaddr);
	new_fd=accept(sfd,(struct sockaddr*)&clientaddr,&addrlen);
	if(new_fd==-1)
	{
		perror("accept");close(sfd);exit(-1);
	}
	printf("%s %d success connect...\n",inet_ntoa(clientaddr.sin_addr),ntohs(clientaddr.sin_port));
	return new_fd;
}

int tcp_connect(const char* ip,int port)
{
	int sfd=socket(AF_INET,SOCK_STREAM,0);
	if(sfd==-1)
	{
		perror("socket");exit(-1);
	}

	struct sockaddr_in serveraddr;
	memset(&serveraddr,0,sizeof(serveraddr));
	serveraddr.sin_family=AF_INET;
	serveraddr.sin_port=htons(port);
	serveraddr.sin_addr.s_addr=inet_addr(ip);

	int ret=connect(sfd,(struct sockaddr*)&serveraddr,sizeof(struct sockaddr));
	if(ret==-1)
	{
		perror("connect");close(sfd);exit(-1);
	}
	return sfd;
}

void signalHandler(void)  //信号处理  让服务器在按下ctrl+c或ctrl+\的时候不会退出
{
	sigset_t sigSet;
	sigemptyset(&sigSet);
	sigaddset(&sigSet,SIGINT);
	sigaddset(&sigSet,SIGQUIT);
	sigprocmask(SIG_BLOCK,&sigSet,NULL);
}
