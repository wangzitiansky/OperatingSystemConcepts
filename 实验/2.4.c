#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

#define INPUT 0
#define OUTPUT 1

int main(){
	pid_t pid_1;
	pid_t pid_2;
	int file_descript_1[2];
	int file_descript_2[2];
	char msg1[] = "Child 1 is sending a message!";
	char msg2[] = "Child 2 is sending a message!";
	char buf_1[256];
	char buf_2[256];

	int resault = 0;

	resault = pipe(file_descript_1);
	if(resault == -1){
		perror("failed to create pipe_1");
		exit(1);
	}

	resault = pipe(file_descript_2);
	if(resault == -1){
		perror("failed to create pipe_2");
		exit(1);
	}

	pid_1 = fork();
	if (pid_1 == -1)
	{
		perror("filed to fork child1");
		exit(1); 
	} else if (pid_1 == 0)
	{
		//第一个子进程里面
		printf("In the child_1\n");
		close(file_descript_1[INPUT]);
		resault = write(file_descript_1[OUTPUT], msg1, (strlen(msg1)+1));
		if (resault == -1)
		{
			perror("filed to write in child_1");
			exit(1);
		}
		close(file_descript_1[OUTPUT]);
		exit(0);
	} else {
		//在父进程里面
		pid_2 = fork();
		if (pid_2 == -1)
		{
			perror("failed to fork child2");
		} else if(pid_2 == 0){
			//在第二个子进程里面
			printf("In th child_2\n");
			close(file_descript_2[INPUT]);
			resault = write(file_descript_2[OUTPUT], msg2, (strlen(msg2)+1));
			if (resault == -1)
			{
				perror("filed to write in child_2");
				exit(1);
			}
			close(file_descript_2[OUTPUT]);
			exit(0);
		} else {
			close(file_descript_2[OUTPUT]);
			resault = read(file_descript_2[INPUT], buf_2, sizeof(buf_2));
			if (resault == -1)
			{
				perror("failed to read from child_2");
				exit(1);
			} else if (resault == 0)
			{
				printf("Read nothing from pip_2\n");
			} else {
				printf("Get message from child_2 = %s\n", buf_2);
			}
			close(file_descript_2[INPUT]);
			close(file_descript_1[OUTPUT]);
			resault = read(file_descript_1[INPUT], buf_1, sizeof(buf_1));
			if (resault == -1)
			{
				perror("failed to read from child_1");
				exit(1);
			} else if (resault == 0)
			{
				printf("Read nothing from pip_1\n");
			} else {
				printf("Get message from child_1= %s\n", buf_1);
			}
			close(file_descript_1[INPUT]);
		}
	}
	return (EXIT_SUCCESS);
}