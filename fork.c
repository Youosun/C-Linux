#include "func.h"

int main()
{
	char ch[20]="hello";
	pid_t pid;
	pid=fork();
	if(0==pid)
	{
		ch[0]='H';
		printf("I am child process,mypid=%d,myppid=%d\n",getpid(),getppid());
		printf("ch=%s add=%p\n",ch,ch);
		return 0;
	}else{
		printf("I am parent process,mychildpid=%d,mypid=%d\n",pid,getpid());
		printf("ch=%s add=%p\n",ch,ch);
		sleep(3);
		return 0;
	}
}
