#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

#define INPUT 0
#define OUTPUT 1

int main()
{
	int file_descriptors[2];
	pid_t pid;
	//message to send
	char *msg = "I have a dream";

	char buf[256];
	int read_count;
	int result;

	//create a pipe
	result = pipe(file_descriptors);

	//创建管道失败
	if (result == -1)
	{
		perror("Failed to calling pipe");
		exit(1);
	}
	//创建子进程
	pid = fork();
	if (pid == -1)
	{
		perror("In the child process...\n");
		exit(1);
	} else if (pid == 0)
	{
		printf("In the child process...\n");
		close(file_descriptors[INPUT]);

		result = write(file_descriptors[OUTPUT], msg, strlen(msg));
		if (result == -1)
		{
			perror("In the child, failed to write into the pipe");
			exit(1);
		}
		close(file_descriptors[OUTPUT]);
		exit(0);
	} else {
		printf("In the parent process...\n");
		close(file_descriptors[OUTPUT]);
		read_count = read(file_descriptors[INPUT], buf, sizeof(buf));
		if (read_count == -1)
		{
			perror("In parent, file to read");
			exit(1);
		} else if (read_count == 0)
		{
			printf("In parnet, 0byte read from pipe\n");			
		} else {
			buf[read_count] = '\0';
			printf("%d bytes of data received from spawned process: %s\n", read_count, buf);
		}
		close(file_descriptors[INPUT]);
	}	
	return (EXIT_SUCCESS);
}