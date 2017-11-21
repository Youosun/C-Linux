#include <stdio.h>
#include <time.h>
#include <pwd.h>
#include <grp.h>
#include <sys/stat.h>
#include <dirent.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#define PERMLEN 10

int getBit(mode_t n,int m)
{
	return (n>>(m-1)) & 1;
}

char *getPerm(mode_t mode,char* perm,int type)
{
	int i;
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
	return perm;
}

char *change_time(const time_t time,char* buf)
{
	int i;
	strcpy(buf,ctime(&time));
	for(i=strlen(buf)-1;i>=0;i--)
	{
		if(buf[i]==':')
		{
			buf[i]='\0';
			break;
		}
	}
	return buf;
}

void printdir(char* path)
{
	DIR* dir = opendir(path);
	if(dir==NULL)
	{
		perror("opendir");
		return;
	}
	struct dirent* p;
	char buf[512];
	char time[50]={0};
	struct stat status;
	char perm[PERMLEN]={0};
	int ret;
	while((p=readdir(dir))!=NULL)
	{
		if(strcmp(p->d_name,".")&&strcmp(p->d_name,".."))
		{
			memset(buf,0,sizeof(buf));
			memset(&status,0,sizeof(status));
			sprintf(buf,"%s%s%s",path,"/",p->d_name);		
			ret=stat(buf,&status);
		    if(ret!=0)
			{
				perror("stat");	
				return;
			}
			printf("%10s %1ld %s %s %6ld %12s %s\n",getPerm(status.st_mode,perm,p->d_type),status.st_nlink,getpwuid(status.st_uid)->pw_name,getgrgid(status.st_gid)->gr_name,status.st_size,change_time(status.st_mtime,time)+4,p->d_name);
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
	printdir(argv[1]);
	return 0;
}
