#include "func.h"

int main(int argc,char** argv)
{
	if(argc!=2)
	{
		printf("error args\n");
		return -1;
	}
	int fd=open(argv[1],O_WRONLY);
	if(fd==-1)
	{
		perror("open");
		return -1;
	}
	int ret=ftruncate(fd,128);
	if(ret!=0)
	{
		perror("ftruncat");
		return -1;
	}
	lseek(fd,0,SEEK_END);
	write(fd,"nihao",5);
	close(fd);
	return 0;
}	
