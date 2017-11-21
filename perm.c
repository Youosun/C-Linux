#include <stdio.h>
#include <sys/types.h>
#define PERMLEN 10

int getBit(mode_t n,int m)
{
	return (n>>(m-1)) & 1;
}

void getPerm(mode_t mode,char* perm,int type)
{
	int i,j=1;
	for(i=1;i<PERMLEN;i++)
	{
		if(getBit(mode,i)&&i%3==1)
		{
			perm[PERMLEN-i]='x';
		}
		else{
			perm[PERMLEN-i]='-';
		}
		if(getBit(mode,i)&&i%3==2)
		{
			perm[PERMLEN-i]='w';
		}
		if(getBit(mode,i)&&i%3==0)
		{
			perm[PERMLEN-i]='r';
		}
	}
	if(type==4)
	{
		perm[0]='d';
	}
	if(type==8)
	{
		perm[0]='-';
	}
	perm[PERMLEN]='\0';
}

int main()
{
	mode_t mode=0x81b4;
	int ret;
	char perm[PERMLEN]={0};
	//ret=getBit(mode,4);
	getPerm(mode,perm,4);
	printf("%s\n",perm);
	//printf("%d\n",ret);
	return 0;
}
