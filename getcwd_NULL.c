#include <unistd.h>
#include <stdio.h>

int main()
{
	char *p=NULL;
	p = getcwd(NULL,0);
	if(NULL==p)
	{
		perror("getcwd");
		return -1;
	}
	printf("%s\n",p);
	return 0;
}
