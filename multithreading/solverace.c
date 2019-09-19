#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int s;

pthread_mutex_t lock;

void* myfunc(void* args){
    pthread_mutex_lock(&lock);
	for (int i = 0; i < 100000; ++i)
	{
		s++;
	}
    pthread_mutex_unlock(&lock);
	return NULL;
}

int main(int argc, char const *argv[])
{
	pthread_t th1;
	pthread_t th2;

    pthread_mutex_init(&lock, NULL);

	pthread_create(&th1, NULL, myfunc, NULL);
	pthread_create(&th2, NULL, myfunc, NULL);
	pthread_join(th1, NULL);
	pthread_join(th2, NULL);
	

    printf("s = %d\n", s);

    return 0;
}
