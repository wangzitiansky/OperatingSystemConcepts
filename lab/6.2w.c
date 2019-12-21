#include<stdio.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<sys/types.h>
#include<string.h>
#include<errno.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>

#define BUF_SIZE 1024
#define SHM_KEY 0x2048

typedef struct shmseg
{
	int cnt;
	char buf[BUF_SIZE];
}shmseg;

int fill_buffer(char* bufptr, int size){
	int filled_count;
	char ch = 'A';
	memset(bufptr, ch, size - 1);
	bufptr[size - 1] = '\0';
	filled_count = strlen(bufptr);
	return filled_count;
}

int main(int argc, char const *argv[])
{
	int shmid;
	shmseg* shmp;
	char* bufptr;
	int space_availabel;
	// 内核中不存在和key值相等的共享内存则创造一个 存在则报错
	shmid = shmget(SHM_KEY, sizeof(shmseg) * BUF_SIZE, 0666|IPC_CREAT);
	if (shmid == -1)
	{
		perror("获取共享内存失败");
		return 1;
	}
	// 内核标识符  存在地址 NULL为自动地址 读写模式
	shmp = (shmseg*)shmat(shmid, NULL, 0);
	if (shmp == (void*) -1)
	{
		perror("共享内存映射失败");
		return 1;
	}
	bufptr = shmp -> buf;

	shmp -> cnt = fill_buffer(bufptr, BUF_SIZE - 1);
	printf("写了 %d bytes\n", shmp -> cnt);
	if (shmdt(shmp) == -1)
	{
		perror("shmdt");
		return 1;
	}
	printf("finished\n");
	return 0;
}