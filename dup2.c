#include "func.h"

int main(int argc,char** argv)
{
	int fd=open(argv[1],O_RDWR);
	close(1);
	int newfd=dup2(fd,1);
	if(newfd==-1)
	{
		perror("dup2");
		return -1;
	}
	printf("newfd=%d\n",newfd);
	write(newfd,"hello\n",6);
	return 0;
}
