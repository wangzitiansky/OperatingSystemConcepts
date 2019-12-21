#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

void sig_myself(int);

int main(int argc, char const *argv[])
{

	

	pid_t pid;
	pid = fork();
	if (pid == -1)
	{
		perror("Failed in calling fork");
		exit(1);
	} else if (pid == 0)
	{
		if (signal(SIGINT, sig_myself) == SIG_ERR)
		{
			printf("can not catch sigint\n");
			exit(1);
		}
		for (; ; )
		// 让进城暂停知道信号出现
			pause();
	} else {
		if (signal(SIGINT, sig_usr) == SIG_ERR)
		{
			printf("can not catch sigint\n");
			exit(1);
		}
			printf("在父进程中 pid = %d ppid = %d\n",getpid(), getppid() );
		for (; ; )
		// 让进城暂停知道信号出现
			pause();	
	}

	
	return 0;
}

void sig_myself(int signo){
	if (signo == SIGINT)
	{
		printf("reveived SIGINT\n");
		printf("received signal %d\n", signo);
		printf("进程ID是 %d\n", getpid());
		printf("父进程ID是 %d\n", getppid());
	} else {
		printf("received signal %d\n", signo);
		exit(1);
	}
}
