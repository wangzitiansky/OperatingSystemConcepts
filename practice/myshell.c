#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define MAX_VALUE 80

typedef struct node
{
	char* command;
	struct node* next;	
}LinkedList;

LinkedList* add(LinkedList* p, char* msg){
	LinkedList* q = (LinkedList*)malloc(sizeof(LinkedList));
	p -> next = q;
	q -> next = NULL;
	q -> command = malloc(strlen(msg) + 1);
	strcpy(q -> command, msg);
	return q;
}

void print(LinkedList* head){
	if (head == NULL)
	{
		return;
	}
	head = head -> next;
	while(head != NULL){
		printf("%s\n", head -> command);
		head = head -> next;
	}
	
}
 
void freeList(LinkedList* head){
	LinkedList* temp = head;
	while(head != NULL){
		temp = head -> next;
		free(head -> command);
		free(head);
		head = temp;
	}
}

int main(void)
{
	LinkedList* head = (LinkedList*)malloc(sizeof(LinkedList));
	head -> command = malloc(strlen("head") + 1);
	LinkedList* start = head;
	strcpy(head -> command, "head");
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
			freeList(head);
			break;
		}
        //printf("args = %s\n", args);

		if (strncmp(args, "history", 7) == 0)
		{
			print(head);
		}

		LinkedList* pList = add(start, args);
		start = pList;

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
