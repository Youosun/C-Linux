#include "func.h"

int main(int argc,char** argv)
{
	if(argc!=2)
	{
		printf("error args\n");
		return -1;
	}	
	int fd=open(argv[1],O_RDWR);
	if(fd==-1)
	{
		perror("open");
		return -1;
	}
	int ret=lseek(fd,512,SEEK_CUR);
	printf("ret=%d\n",ret);
	write(fd,"end",3);
	char buf[1024]={0};
	lseek(fd,0,SEEK_SET);
	read(fd,buf,sizeof(buf));
	printf("buf=%s\n",buf);
	close(fd);
	return 0;
}
			
