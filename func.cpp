#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void MyPrint(const char *pszSrc)
{
	printf("The string is %s\n",pszSrc);
}

void MyPrint2(const char *pszSrc)
{
	char *pszRev;
	int i,ilen;
	ilen = strlen(pszSrc);
	pszRev=(char*)malloc(ilen+1);
	for(i=0;i<ilen;i++)
	{
		pszRev[i]=pszSrc[ilen-i-1];
	}
	pszRev[ilen]='\0';
	printf("The revert string is %s\n",pszRev);
	free(pszRev);
}
