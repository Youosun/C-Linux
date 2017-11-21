#include "factory.h"

void send_data(int new_fd)
{
	train t;
	memset(&t,0,sizeof(t));
	strcpy(t.buf,FILENAME);
	t.len=strlen(t.buf);
	int ret;
	ret=send_n(new_fd,(char*)&t,t.len+4);
	if(ret!=0)
	{
		perror("send");exit(-1);
	}
	int fd;
	fd=open(FILENAME,O_RDONLY);	
	if(-1==fd)
	{
		perror("open");exit(-1);
	}
	struct stat buf;
	bzero(&buf,sizeof(buf));
	fstat(fd,&buf);
	memcpy(t.buf,&buf.st_size,sizeof(buf.st_size));
	t.len=sizeof(buf.st_size);
	send_n(new_fd,(char*)&t,t.len+4);
	while(memset(&t,0,sizeof(t)),(t.len=read(fd,t.buf,sizeof(t.buf)))>0)
	{
		send_n(new_fd,(char*)&t,t.len+4);
	}
	t.len=0;
	send_n(new_fd,(char*)&t,4+t.len);
	close(new_fd);
}
