#include "func.h"

int main()
{
	printf("execl_pid=%d\n",getpid());
	execl("./add","add","5","6",NULL);
	return 0;
}
