#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>

int globvar = 6;
int main(int argc, char const *argv[])
{
	int var;
	pid_t pid;

	var = 88;
	printf("Before fork\n");
	if ((pid = fork()) < 0)
	{
		return 1;
	} else if (pid == 0)
	{
		fprintf(stderr, "Fork Success");
		globvar++;
		var++;
	} else {
		//休眠父进程 让子进程先执行
		sleep(2);
	}
	printf("pid = %ld, glob = %d,var = %d\n",(long)getpid(), globvar, var);
	return 0;
}