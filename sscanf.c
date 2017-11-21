#include <stdio.h>
#include <string.h>

int main()
{
	int age;
	char name[10];
	float score;
	char addr[20]={0};
	char buf[50]="10 lele 85.5 shenzhen";
	sscanf(buf,"%d%s%f%s",&age,name,&score,addr);
	printf("%d %s %5.3f %s\n",age,name,score,addr);
	return 0;
}
