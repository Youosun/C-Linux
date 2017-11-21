#include "func.h"
void sig(int sigNum,siginfo_t *p,void *p1)
{
	printf("I am a signal %d\n",sigNum);
	signal(sigNum,SIG_DFL);
}

int main()
{
	struct sigaction act;
	memset(&act,0,sizeof(act));
	act.sa_sigaction=sig;
	act.sa_flags=SA_SIGINFO;
	int ret;
	ret=sigaction(SIGINT,&act,NULL);
	if(ret==-1)
	{
		perror("sigaction");exit(-1);
	}
	while(1);
}
