#include "func.h"
void sig(int sigNum,siginfo_t *p,void *p1)
{
	printf("before sleep I am a signal %d\n",sigNum);
	sleep(2);
	printf("after sleep I am a signal %d\n",sigNum);
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
	ret=sigaction(SIGQUIT,&act,NULL);
	if(ret==-1)
	{
		perror("sigaction1");exit(-1);
	}
	while(1);
}
