#include <sys/stat.h>
#include <stdio.h>

int main(int argc,char *argv[])
{
	int ret;
	if(argc!=2)
	{
		printf("error args\n");
		return -1;
	}
	ret=chmod(argv[1],0666);
	if(ret!=0)
	{
		perror("chmod");
	}
	return 0;
}
