#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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

int main(int argc, char const *argv[])
{
	LinkedList* head = (LinkedList*)malloc(sizeof(LinkedList));
	head->command = malloc(strlen("head") + 1); 
	strcpy(head -> command, "head");
	LinkedList* q = add(head, "head->next");
	LinkedList* qnext = add(q, "head->next->next");
	print(head);
	freeList(head);
	return 0;
}