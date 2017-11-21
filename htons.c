#include "func.h"

int main()
{
	short port=0x1234;
	short net_port;
	net_port=htons(port);
	printf("net_port=%x\n",net_port);
	short ret;
	ret=ntohs(net_port);
	printf("ret=%x\n",ret);
	return 0;
}
