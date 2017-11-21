#include "func.h"

int main(int argc,char** argv)
{
	if(argc!=2)
	{
		printf("error args");
		return -1;
	}
	int fd;
	umask(0);
	fd=open(argv[1],O_RDONLY|O_CREAT|O_EXCL,0777);
	if(-1==fd)
	{
		perror("open");
		return -1;
	}
	printf("fd=%d\n",fd);
	return 0;
}
