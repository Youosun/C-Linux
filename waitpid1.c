#include "func.h"

int main()
{
	pid_t cpid;
	cpid=fork();
	if(cpid==0)
	{
		printf("I am child process,pid=%d ppid=%d\n",getpid(),getppid());
		exit(5);
	}else{
		printf("I am parent process,pid=%d\n",getpid());
		int status;
		while(1)
		{
			pid_t retpid;
			retpid=waitpid(cpid,&status,WNOHANG);
			if(retpid!=0)
			{
				break;
			}
		}
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
		
