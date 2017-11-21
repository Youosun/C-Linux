#include <stdio.h>
#include <unistd.h>

int main(int argc,char* argv[])
{
	if(argc!=2)
	{
		printf("error args\n");
		return -1;
	}
	int ret;
	ret = rmdir(argv[1]);
	if(ret!=0)
	{
		perror("rmdir");
		return -1;
	}
	return 0;
}
