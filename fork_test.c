#include "head.h"

int exitfds[2];

void handler(int signum,siginfo_t* p,void* q)
{
	printf("signum=%d\n",signum);
	int ret;
	ret=write(exitfds[1],&signum,sizeof(int));
	printf("handler send signal success,ret=%d\n",ret);
}

int main()
{
	pid_t pid;
	pipe(exitfds);
	pid=fork();
	if(!pid)
	{
		close(exitfds[1]);
		int sigcom;
		read(exitfds[0],&sigcom,sizeof(int));
		printf("child get signal=%d\n",sigcom);
		exit(2);
	}else{
		close(exitfds[0]);
		struct sigaction act;
		memset(&act,0,sizeof(act));
		sigemptyset(&act.sa_mask);
		act.sa_sigaction=handler;
		act.sa_flags=SA_SIGINFO;
		if(sigaction(SIGQUIT,&act,NULL)==-1)
		{
			perror("sigaction");exit(-1);\
		}
		int status;
		waitpid(pid,&status,0);
		printf("child ret=%d\n",WTERMSIG(status));
	}
}
	
