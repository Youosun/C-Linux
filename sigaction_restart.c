#include "func.h"
void sig(int sigNum,siginfo_t *p,void *p1)
{
	printf("I am a signal %d\n",sigNum);
}

int main()
{
	struct sigaction act;
	memset(&act,0,sizeof(act));
	act.sa_sigaction=sig;
	act.sa_flags=SA_SIGINFO|SA_RESTART;
	int ret;
	ret=sigaction(SIGINT,&act,NULL);
	if(ret==-1)
	{
		perror("sigaction");exit(-1);
	}
	char buf[20]={0};
	read(0,buf,sizeof(buf));
	printf("%s",buf);
	exit(0);
}
