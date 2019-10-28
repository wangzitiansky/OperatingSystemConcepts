#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

void* myfunc_1(void* args){
	char* arg = (char*)args;
	printf("%s\n", arg);
	return NULL;
}

void* myfunc_2(void* args){
	int* arg = (int*)args;
	printf("%d\n", *arg);
	return NULL;
}

int main(int argc, char const *argv[])
{
	pthread_t th1;
	pthread_t th2;
	char arg1[] = "thread_1";
	int arg2 = 1234;

	pthread_create(&th1, NULL, myfunc_1, arg1);
	pthread_create(&th2, NULL, myfunc_2, &arg2);
	pthread_join(th1, NULL);
	pthread_join(th2, NULL);
	printf("the end\n");
	return 0;
}