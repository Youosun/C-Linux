#include "func.h"

int main()
{
	int ret;
	ret=mkfifo("1.fifo",0777);
	if(ret==-1)
	{
		perror("mkfifo");
		return -1;
	}
	return 0;
}
