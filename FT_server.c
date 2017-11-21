#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/fcntl.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <pthread.h>

#define DEFAULT_SVR_PORT 2828
#define FILE_MAX_LEN 64
char filename[FILE_MAX_LEN+1];

static void* handle_client(void* arg)
{
	int sock=(int)arg;
	char buf[1024];
	int len;
	printf("begin send\n");
	FILE* fp=fopen(filename,"r");
	if(fp==NULL)
	{
		close(sock);
		exit(-1);
	}
	if(send(sock,filename,FILE_MAX_LEN,0)==-1)
	{
		perror("send file name\n");
		if(fp)
		{
			fclose(fp);
		}
		close(sock);
		exit(-1);
	}
	printf("begin send file %s...\n",filename);
	while(!feof(file))
	{
		memset(buf,0,sizeof(buf));
		len=fread(buf,1,sizeof(buf),fp);
		printf("server read %s,len %d\n",filename,len);
		if(send(sock,buf,len,0)<0)
		{
			perror("send file:");
			if(fp)
			{
				close(fp);
			}
			close(sock);
			exit(-1);
		}
	}
}

int main(int argc,char* argv[])
{
	int sockfd,new_fd;
	struct sockadddr_in my_addr;
	struct sockaddr_in their_addr;
	int sin_size,numbytes;
	pthread_t cli_thread;
	unsigned short port;
	if(argc<2)
	{
		printf("need a filename without path\n");
		exit(-1);
	}
	strncpy(filename,argv[1],FILE_MAX_LEN);
	port=DEFAULT_SVR_PORT;
	if(argc>=3)
	{
		port=(unsigned short)atoi(argv[2]);
	}
	if((sockfd=socket(AF_INET,SOCK_STREAM,0))==-1)
	{
		perror("socket");exit(-1);
	}
	memset(&my_addr,0,sizeof(myaddr));
	my_addr.sin_family=AF_INET;
	my_addr.sin_port=htons(port);
	my_addr.sin_addr.s_addr=INADDR_ANY;
	if(bind(sockfd,(struct sockaddr*)&my_addr,sizeof(struct sockaddr))==-1)
	{
		perror("bind");
		close(sockfd);
		exit(-1);
	}
	if(listen(sfd,10)==-1)
	{
		perror("listen");
		close(sockfd);
		exit(-1);
	}
	printf("#@ listen port %d\n",port);
	while(1)
	{
		sin_size=sizeof(struct sockaddr_in);
		printf("server waiting...\n");
		if((new_fd=accept(sockfd,(struct sockaddr*)&their_addr,&sin_size))==-1)
		{
			perror("accept");
			close(sockfd);
			exit(-1);
		}
		printf("---clien (ip=%s:port=%d) request\n",inet_ntoa(their_addr.sin_addr),ntohs(their_addr.sin_port));
		pthread_create(&cli_thread,NULL,handle_client,(void*)new_fd);
	}
	exit(0);
}
