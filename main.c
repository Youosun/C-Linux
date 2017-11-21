#include <stdio.h>
void print()
{
	char *p=NULL;
	*p='f';
	printf("I can run\n");
}

int main()
{
	int i=5;
	print();
	printf("I am main\n");
	return 0;
}
