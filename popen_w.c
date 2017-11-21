#include "func.h"

int main()
{
	FILE* fp;
	fp=popen("./add","w");				//将返回的fp定位到程序add的标准输入中   创建子进程  并建立管道连接
	if(fp==NULL)
	{
		perror("popen");
		return -1;
	}
	fwrite("15 6",sizeof(char),4,fp);
	pclose(fp);                          //使用管道后不关闭  将到时子进程add变为孤儿进程   只有写端关闭时  add的读端才会读取到数据
	return 0;
}
