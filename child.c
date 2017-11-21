#include "func.h"
void recv_fd(int fdr,int* fd);
void send_data(int fd);

void child_handler(int fdr)
{
	int fd;
	char flag=1;
	while(1)
	{	
		recv_fd(fdr,&fd);						//子进程接受父进程发来的描述符，并向其发送文件  完成后向父进程发送flag
		send_data(fd);
		write(fdr,&flag,sizeof(flag));
	}
}

void make_children(pchild p,int child_num)		//创建多个子进程  同时初始化子进程状态信息
{
	int fds[2];
	pid_t pid;
	int i;
	for(i=0;i<child_num;i++)
	{
		socketpair(AF_LOCAL,SOCK_STREAM,0,fds);	//初始化全双工的管道  参数记住
		pid=fork();
		if(pid==0)								//生成的子进程处理业务流程---发送文件
		{
			close(fds[1]);
			child_handler(fds[0]);
		}else{
			close(fds[0]);
			p[i].pid=pid;
			p[i].busy=0;
			p[i].tfds=fds[1];
		}
	}
}
