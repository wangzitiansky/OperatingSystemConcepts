#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdlib.h>
#include <dispatch/dispatch.h>
#define Buffer_Limit 5
#define DATA_1 0
#define DATA_2 1

int buffer[Buffer_Limit];

int Buffer_In = 0;
int Buffer_Out = 0;
int data[2] = { -1, -1};

dispatch_semaphore_t empty;
dispatch_semaphore_t full;
pthread_mutex_t lock;

void* Consumer(void* args){
	int self = *((int*) args);
	int n = 1;
	while(n++ <= 10){
		dispatch_semaphore_wait(full, DISPATCH_TIME_FOREVER);
		pthread_mutex_lock(&lock);
		// printf("Buffer_Out = %d\n", Buffer_Out);
		int num = buffer[Buffer_Out];
		Buffer_Out = (Buffer_Out + 1) % Buffer_Limit;
		printf("Consumer: %d from %d\n", num, self);
		// for (int i = 0; i < Buffer_Limit; ++i)
		// {
		// 	printf("buffer = %d\n", buffer[i]);
		// }
		if (num == -1)
		{
			break;
		}
		if (self == 2)
		{
			if (data[DATA_1] != -1)
		 	{
		 		printf("sum = %d mul = %d\n", num + data[DATA_1], num * data[DATA_1]);
		 		data[0] = -1;
		 		data[1] = -1;
		 	} else {
		 		data[DATA_2] = num;
		 	}
	 	} else {
	 		if (data[DATA_2] != -1)
		 	{
		 		printf("sum = %d mul = %d\n", num + data[DATA_2], num * data[DATA_2]);
		 		data[0] = -1;
		 		data[1] = -1;
		 	} else {
		 		data[DATA_1] = num;
		 	}
	 	}
	 	pthread_mutex_unlock(&lock);
		dispatch_semaphore_signal(empty);
	}
	return NULL;
}

void* Producer(void* args){
	char* filename = (char*) args;
	int arr[11] = {};
	int ch;
	FILE* fp = fopen(filename, "r");
	int num;
	int len = 0;
	while(fscanf(fp, "%d", &num) != EOF){
		arr[len] = num;
		len++;
	}
	for (int i = 0; i < len; ++i)
	{
		ch = arr[i];
		dispatch_semaphore_wait(empty, DISPATCH_TIME_FOREVER);
		pthread_mutex_lock(&lock);
		buffer[Buffer_In] = ch;
		
		printf("Producer:%d from %s\n", buffer[Buffer_In], filename);
		// 生产一个就去唤醒
		Buffer_In = (Buffer_In + 1) % Buffer_Limit;
		
		pthread_mutex_unlock(&lock);
		dispatch_semaphore_signal(full);

	}
	return NULL;
}

int main(int argc, char const *argv[])
{
	pthread_t producer1_thread_id, consumer1_thread_id, producer2_thread_id, consumer2_thread_id;
	char file_1[] = "data1.txt";
	char file_2[] = "data2.txt";
	int name[2] = { 1, 2 }; 
	empty = dispatch_semaphore_create(5);
	full = dispatch_semaphore_create(0);
	pthread_mutex_init(&lock, NULL);  
	pthread_create(&producer1_thread_id, NULL, Producer, file_1);
	pthread_create(&producer2_thread_id, NULL, Producer, file_2);
	pthread_create(&consumer1_thread_id, NULL, Consumer, &name[0]);
	pthread_create(&consumer2_thread_id, NULL, Consumer, &name[1]);
	pthread_join(producer1_thread_id, NULL);
	pthread_join(producer2_thread_id, NULL);
	pthread_join(consumer1_thread_id, NULL);	
	pthread_join(consumer2_thread_id, NULL);
	return 0;
}