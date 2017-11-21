#include "func.h"

int main(int argc,char* argv[])
{
	if(argc!=2)
	{
		printf("error args\n");exit(-1);
	}
	int ret;
	struct in_addr addr;
	ret=inet_aton(argv[1],&addr);
	if(ret==0)
	{
		printf("inet_aton failed ret=%d\n",ret);
		exit(-1);
	}
	printf("addr=%x\n",addr.s_addr);
	printf("ip=%s\n",inet_ntoa(addr));
	printf("addr.s_addr=%x\n",inet_addr(argv[1]));
	return 0;
}
