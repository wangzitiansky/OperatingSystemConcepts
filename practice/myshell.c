#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define MAX_VALUE 80

typedef struct List{
    char* command;
    struct List* next;
}LinkedList;

int main(void)
{
	while(1){
		char args[MAX_VALUE] = { };
		char* array[sizeof(args)] = { };
		char* p = NULL;
		pid_t pid;
		int status;
		int i = 0;
		//命令提示语句
		printf("osh>");
		fgets(args, sizeof(args), stdin);
		fflush(stdout);

		if (args[strlen(args) - 1] == '\n')
		{
			args[strlen(args) - 1] = 0;
		}
		//退出
		if (strncmp(args, "exit", 4) == 0)
		{
			break;
		}
        //printf("args = %s\n", args);
		p = strtok(args, " ");
		while(p != NULL){
            if(*p != ' '){
		    	array[i++] = p;
            } else {
            	array[i++] = NULL;
            }
			p = strtok(NULL, " ");
		}

		// for (int i = 0; *(array+i) != NULL; ++i)
		// {
		// 	printf("array = %s\n", *(array+i));
		// }
		//创建进程
		if ((pid = fork()) < 0)
		{
			printf("fork error");
		} else if (pid == 0)
		{
			execvp(array[0], array);
		    exit(127);
        }
//        if(args[strlen(args) - 2] != '&'){
            if((pid = waitpid(pid, &status, 0)) < 0){
                printf("waitpit error");
            }
  //      }
	
	}
	return 0;
}
