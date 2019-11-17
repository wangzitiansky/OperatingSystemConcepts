#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

void* myfunc(void* args){
	char* arg = (char*)args;
	printf("int the %s\n", arg);
	return NULL;
}

int main(int argc, char const *argv[])
{
	pthread_t th1;
	pthread_t th2;
	char arg1[] = "thread_1";
	char arg2[] = "thread_2";

	pthread_create(&th1, NULL, myfunc, arg1);
	pthread_create(&th2, NULL, myfunc, arg2);
	pthread_join(th1, NULL);
	pthread_join(th2, NULL);
	printf("the end\n");
	return 0;
}