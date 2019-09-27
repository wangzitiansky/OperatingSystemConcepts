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
		// ----- A -----
		sleep(3);
		//------- B -------
		//exit(0);
		//子进程没结束 before return输出两遍
	} else {
		printf("In the parent process, child's PID = %d\n", pid);
		printf("In parent process, PID = %d , PPID = %d \n", getpid(), getppid());
	
		// ----c-----
		//wait(NULL);
		//父进程没有等子进程 父进程先结束了
		//如果一个进程的父进程先于自己结束了 则系统将其父进程的ID 设为1
	}
	printf("Before return in main(), PID  = %d , PPID = %d \n", getpid(), getppid());
	return 0;
}