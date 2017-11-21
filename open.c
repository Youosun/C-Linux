#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>

int main(int argc,char** argv)
{
	if(argc!=2)
	{
		printf("error args\n");
		return -1;
	}
	int fd;
	umask(0);
	fd=open(argv[1],O_WRONLY,0777);
	if(-1==fd)
	{
		perror("open");
		return -1;
	}
	printf("%d\n",fd);
	close(fd);
	return 0;
}
