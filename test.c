#include "func.h"

typedef struct {
	int flag;
	char buf[10];
}data,*pdata;

int main()
{
	pdata a;
	a=(pdata)calloc(1,sizeof(data));
	a->flag=0;
	strcpy(a->buf,"hello");
	printf("%d %s\n",a->flag,a->buf);
	exit(0);
}
