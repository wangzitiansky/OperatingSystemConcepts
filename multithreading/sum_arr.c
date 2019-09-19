#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

typedef struct{
    int first;
    int last;
    int resault;
} MY_ARGS;

int arr[5000];

void* myfunc(void* args){
    int sum = 0;
    MY_ARGS* my_args = (MY_ARGS*) args;
    int first = my_args -> first;
    int last = my_args -> last;
	for (int i = first; i < last; ++i)
	{
		sum  = sum + arr[i];
	}
    my_args -> resault = sum;
	return NULL;
}

int main(int argc, char const *argv[])
{
    int i;
    for(int i = 0; i < 5000; i++){
        arr[i] = rand() % 50;
    }
    
	pthread_t th1;
	pthread_t th2;

    MY_ARGS args1 = {0, 2501, 0};
    MY_ARGS args2 = {2501, 5000, 0};

	pthread_create(&th1, NULL, myfunc, &args1);
	pthread_create(&th2, NULL, myfunc, &args2);
	pthread_join(th1, NULL);
	pthread_join(th2, NULL);
	
    int sum1 = args1.resault;
    int sum2 = args2.resault;

    printf("sum1 = %d\n", sum1);
    printf("sum2 = %d\n", sum2);
    printf("sum = %d\n", sum1 + sum2);

    return 0;
}
