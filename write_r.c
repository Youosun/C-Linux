#include "func.h"

int main(int argc,char** argv)
{	
	if(argc!=3)
	{
		printf("error args\n");
		return -1;
	}
	int fdw=open(argv[1],O_WRONLY);
	if(-1==fdw)
	{
		perror("open");
		return -1;
	}
	int fdr=open(argv[2],O_RDONLY);
	if(-1==fdr)
	{
		perror("open");
		return -1;
	}
	int ret;
	char buf[20]={0};
	fd_set rset;
	while(1)
	{
		FD_ZERO(&rset);
		FD_SET(0,&rset);
		FD_SET(fdr,&rset);
		select(fdr+1,&rset,NULL,NULL,NULL);
		if(FD_ISSET(0,&rset))
		{
			memset(buf,0,sizeof(buf));
			read(0,buf,sizeof(buf));
			write(fdw,buf,strlen(buf)-1);
		}
		if(FD_ISSET(fdr,&rset))
		{
			memset(buf,0,sizeof(buf));
			read(fdr,buf,sizeof(buf));
			printf("%s\n",buf);
		}
	}
	close(fdr);
	close(fdw);
	return 0;
}	
