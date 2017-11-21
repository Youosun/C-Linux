#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>

int main(int argc,char** argv)
{
	if(argc!=2)
	{
		printf("error args\n");
		return -1;
	}
	struct stat status;
	int ret;
	memset(&status,0,sizeof(struct stat));
	ret=stat(argv[1],&status);
    if(ret!=0)
	{
		perror("stat");	
		return -1;
	}
	printf("inode=%ld mode=%x link=%ld uid=%u gid=%u size=%ld blksize=%ld blkcnt=%ld time=%ld\n",status.st_ino,status.st_mode,status.st_nlink,status.st_uid,status.st_gid,status.st_size,status.st_blksize,status.st_blocks,status.st_mtime);
	return 0;
}
