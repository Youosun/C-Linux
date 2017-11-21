#include <unistd.h>
#include <stdio.h>

int main()
{
	printf("%s\n",getcwd(NULL,0));
	int ret;
	ret = chdir("/");
	if(ret!=0)
	{
		perror("chdir");
		return -1;
	}
	printf("%s\n",getcwd(NULL,0));
	return 0;
}
