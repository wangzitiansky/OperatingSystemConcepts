#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

typedef struct 
{
	int first;
}MY_ARGS;

void* my_func(void* args){
	MY_ARGS* arg = (MY_ARGS*)args;
	arg -> first = -1;
	return NULL;
}

int main(int argc, char const *argv[])
{
	pthread_t th1;
	MY_ARGS args = { 1 };
	pthread_create(&th1, NULL, my_func, &args);
	pthread_join(th1, NULL);
	printf("%d\n", args.first);
	return 0;
}