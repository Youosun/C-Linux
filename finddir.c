#include <stdio.h>
#include <dirent.h>
#include <sys/types.h>
#include <string.h>

void printdir(char* path,int width)
{
	DIR* dir = opendir(path);
	if(dir==NULL)
	{
		perror("opendir");
		return;
	}
	struct dirent* p;
	char buf[512];
	while((p=readdir(dir))!=NULL)
	{
		if(strcmp(p->d_name,".")&&strcmp(p->d_name,".."))
		{
			printf("%*s%s\n",width,"",p->d_name);
			if(p->d_type==4)
			{
				bzero(buf,sizeof(buf));
				sprintf(buf,"%s%s%s",path,"/",p->d_name);
				printdir(buf,width+4);
			}
		}
	}
} 

int main(int argc,char* argv[])
{
	if(argc!=2)
	{
		printf("error args\n");
		return -1;
	}
	printdir(argv[1],0);
	return 0;
}

