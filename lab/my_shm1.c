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
#define SHM_KEY 0x1234
typedef struct shmseg
{
	int cnt;
	char buf[BUF_SIZE];
}shmseg;

int main(int argc, char const *argv[])
{
	int shmid;
	int spacevailabel;
	char* bufptr;
	shmid = shmget(SHM_KEY, sizeof(struct shmseg), 0644|IPC_CREAT);
	if (shmid == -1)
	{
		perror("Shared memory");
		return 1;
	}
	shmp = shmat(shmid, NULL, 0);
	if(shmp == (void*) -1){
		perror("Shared memory shmat error");
		return 1;
	}
	bufptr = shmp -> buf;
	spacevailabel = BUF_SIZE;
	
	shmp -> cnt = fill_buffer(bufptr, spacevailabel);
	printf("Writing Process: Shared Memory Write: Wrote %d bytes\n", shmp->cnt);
	bufptr = shmp -> buf;

	if (shmdt(shmp) == -1)
	{
		perror("shmdt");
		return 1;
	}
	if (shmctl(shmid, IPC_CREAT, 0) == -1)
	{
		perror("shmctl");
		return 1;
	}
	printf("okkkkk\n");
	
	return 0;
}