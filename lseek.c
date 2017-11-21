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
	int ret=lseek(fd,2,SEEK_CUR);
	printf("ret=%d\n",ret);
	char buf[32]={0};
	read(fd,buf,sizeof(buf)-1);
	printf("buf=%s\n",buf);
	close(fd);
	return 0;
}
			
