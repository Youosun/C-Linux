#include <unistd.h>
#include <stdio.h>

int main()
{
	char path[256]={0};
	if(getcwd(path,sizeof(path))==NULL)
	{
		perror("getcwd");
		return -1;
	}
	printf("%s\n",path);
	return 0;
}
