#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

int main()
{
	pid_t pid;

	printf("Before fork, PID = %d, PPID = %d \n",getpid(), getppid() );

	pid = fork();
	if (pid == -1)
	{
		perror("Failed in calling fork");
		exit(1);
	} else if (pid == 0)
	{
		printf("In child process, PID = %d , PPID = %d \n", getppid(), getppid());
		exit(0);
	} else {
		printf("In the parent process, child's PID = %d\n", pid);
		printf("In parent process, PID = %d , PPID = %d \n", getpid(), getppid());
		wait(NULL);
	}
	printf("Before return in main(), PID  = %d , PPID = %d \n", getpid(), getppid());
	return 0;
}