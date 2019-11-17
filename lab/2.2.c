#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

int main()
{
	pid_t result1;
	pid_t result2;

	printf("<A> -- pid = %d, ppid = %d\n", getpid(), getppid());

	result1 = fork();

	if (result1 < 0)
	{
		perror("Failed to create process after <A>");
	}

	printf("<B> ---- pid = %d , ppid = %d , result1 = %d\n", getpid(), getppid(), result1);

	result2 = fork();
	if (result2 < 0)
	{
		perror("Failed to create the process after <B>");
	}

	printf("<C> --- pid = %d , ppid = %d , result2 = %d\n", getpid(), getppid(), result2);

	sleep(2);
	return(EXIT_SUCCESS);
}