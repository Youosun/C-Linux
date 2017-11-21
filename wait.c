#include "func.h"

int main()
{
	if(!fork())
	{
		sleep(5);
		printf("I am child process,pid=%d ppid=%d\n",getpid(),getppid());
		return 5;
	}else{
		printf("I am parent process,pid=%d\n",getpid());
		int status;
		pid_t cpid;
		cpid=wait(&status);
		printf("wait child success,child pid=%d status=%x\n",cpid,status);
		if(WIFEXITED(status))
		{
			printf("child exit status=%d\n",WEXITSTATUS(status));
		}else{
			printf("child crashed\n");
		}
		return 0;
	}
}
		
