#include "head.h"

int send_n(int new_fd,char* p,int len)
{
	int total=0;
	int ret;
	while(total<len)
	{
		ret=send(new_fd,p+total,len-total,0);
		total=total+ret;
	}
	return 0;
}

int recv_n(int sfd,char* p,int len)
{
	int total=0;
	int ret;
	while(total<len)
	{
		ret=recv(sfd,p+total,len-total,0);
		total=total+ret;
	}
	return 0;
}
