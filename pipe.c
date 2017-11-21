#include "func.h"

int main()
{
	int fds[2];				//如果需要进行双向通信需要再申请一个fds[2]   如果存在多个子进程 都需要与父进程相互通信  则共需要2*n个fds[2]  n为子进程数目
	int ret=pipe(fds);
	if(ret!=0)
	{
		perror("pipe");
		return -1;
	}
	if(!fork())
	{
		close(fds[1]);			//关闭写端
		char buf[20]={0};
		read(fds[0],buf,sizeof(buf));
		puts(buf);
		exit(0);
	}else{
		close(fds[0]);			//关闭读端
		write(fds[1],"I am writer",11);   
		wait(NULL);
		exit(0);
	}
}
