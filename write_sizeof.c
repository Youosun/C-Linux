#include "func.h"

int main(int argc,char** argv)
{
	if(argc!=2)
	{
		printf("error args\n");
		return -1;
	}
	int fd=open(argv[1],O_RDWR);
	if(-1==fd)
	{
		perror("open");
		return -1;
	}
	ssize_t ret;
	char buf[512]="hello world";
	ret=write(fd,buf,sizeof(buf));
	if(ret==-1)
	{
		perror("write");
		return -1;
	}
	printf("write=%ld\n",ret);
	return 0;
}
