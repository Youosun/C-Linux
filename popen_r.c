#include "func.h"

int main()
{
	FILE* fp;
	fp=popen("ls","r");          			//读取command参数的标准输出  管道定向到程序的STDOUT
	char buf[512]={0};
	if(fp==NULL)
	{
		perror("popen");
		return -1;
	}
	fread(buf,sizeof(char),sizeof(buf),fp);	//读取ls真实的输出  每输出一行均有换行符
	printf("%s",buf);
    pclose(fp);                          
	return 0;
}
