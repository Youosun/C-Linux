#include <stdio.h>
#include <string.h>

int main()
{
	int age =10;
	char name[5]="lele";
	float score = 85.5;
	char addr[20]="shenzhen";
	char buf[50];
	memset(buf,0,sizeof(buf));
	sprintf(buf,"%d %s %5.2f %s",age,name,score,addr);
	puts(buf);
	return 0;
}
