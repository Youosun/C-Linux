#include "func.h"
int print()
{
	printf("I am print func\n");
	exit(1);
}

int main()
{
	print();
	abort();
	printf("I am main\n");
	return 0;
}
