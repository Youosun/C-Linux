#include "func.h"

int main(int argc,char* argv[])
{
	if(argc!=2)
	{
		printf("error args\n");exit(-1);
	}
	struct hostent *content;
	content=gethostbyname(argv[1]);
	if(content==NULL)
	{
		printf("gethostname failed\n");exit(-1);
	}
	printf("real hostname=%s\n",content->h_name);
	int i=0;
	while(content->h_aliases[i]!=NULL)
	{
		printf("h_aliases=%s\n",content->h_aliases[i]);
		i++;
	}
	printf("h_length=%d\n",content->h_length);
	i=0;
	char ip[16]={0};
	while(content->h_addr_list[i]!=NULL)
	{
		memset(ip,0,sizeof(ip));
		inet_ntop(content->h_addrtype,content->h_addr_list[i],ip,sizeof(ip));
		printf("%s\n",ip);
		i++;
	}
	return 0;
}
