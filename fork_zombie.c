#include "func.h"

int main()
{
	if(!fork())
	{
		printf("I am child process,pid=%d ppid=%d\n",getpid(),getppid());
		return 0;
	}else{
		while(1);
		printf("I am parent process,pid=%d\n",getpid());
		return 0;
	}
}
		
