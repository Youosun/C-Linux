#include "func.h"

int main()
{
	int fd=dup(STDIN_FILENO);
	write(fd,"hello\n",6);
	return 0;
}
