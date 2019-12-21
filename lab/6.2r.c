#include<stdio.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<sys/types.h>
#include<string.h>
#include<errno.h>
#include<stdlib.h>

#define BUF_SIZE 1024
#define SHM_KEY 0x2048

typedef struct shmseg {
   int cnt;
   char buf[BUF_SIZE];
}shmseg;

int main(int argc, char const *argv[])
{
	int shmid;
	shmseg* shmp;
	shmid = shmget(SHM_KEY, sizeof(shmseg) * BUF_SIZE, 0666|IPC_CREAT);
	if (shmid == -1)
	{
		perror("创建共享内存错误");
		return 1;
	}
	shmp = (shmseg*)shmat(shmid, NULL, 0);
	if (shmp == (void*) -1)
	{
		perror("内存映射错误");
		return 1;
	}
	printf("comtains: \n\"%s\"\n", shmp->buf);
	printf("read %d bytes\n", shmp->cnt);
	if (shmdt(shmp) == -1)
	{
		perror("shmdt");
		return 1;
	}
	//最后一个参数是共享内存的管理结构体
	if (shmctl(shmid, IPC_RMID, 0) == -1)
	{
		perror("shmid");
		return 1;
	}
	printf("finished\n");
	return 0;
}














