#include "func.h"

int main()
{
	if(!fork())
	{
		printf("before set child pid=%d pgid=%d\n",getpid(),getpgid(0));
		setpgid(0,0);
		printf("after set child pid=%d pgid=%d\n",getpid(),getpgid(0));
		while(1);
	}else{
		printf("parent pid=%d pgid=%d\n",getpid(),getpgid(0));
		while(1);
	}
}
