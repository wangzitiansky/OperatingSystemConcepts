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
#define SHM_KEY 0x1024

typedef struct shmseg
{
	int cnt;
	char buf[BUF_SIZE];
	int complete;
}shmseg;

int fill_buffer(char* bufptr, int size){
	int filled_count;
	static char ch = 'A';
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

	shmid = shmget(SHM_KEY, sizeof(shmseg), 0644|IPC_CREAT);
	if (shmid == -1)
	{
		perror("获取共享内存失败");
		return 1;
	}

	shmp = shmat(shmid, NULL, 0);
	if (shmp == (void*) -1)
	{
		perror("共享内存映射失败");
		return 1;
	}
	bufptr = shmp -> buf;
	space_availabel = BUF_SIZE;

	shmp -> cnt = fill_buffer(bufptr, space_availabel);
	bufptr = shmp -> buf;
	shmp -> complete = 1;
	if (shmdt(shmp) == -1)
	{
		perror("shmdt");
		return 1;
	}
	if (shmctl(shmid, IPC_CREAT, 0) == -1)
	{
		perror("shmid");
		return 1;
	}
	printf("finished\n");
	return 0;
}