#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

int main()
{
	pid_t pid_1;
	pid_t pid_2;

	if ((pid_1 = fork()) < 0)
	{
		perror("Failed to create pid_1");
		exit(1);
	} else if (pid_1 == 0)
	{
		printf("Child_1\n");
	} else {
		printf("Parent\n");

		if ((pid_2 = fork()) < 0)
		{
			perror("Failed to create pid_1");
			exit(1);
		} else if (pid_2 == 0)
		{
			printf("Child_2\n");
		}

		//wait(NULL);
	}

	return 0;
}