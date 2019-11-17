#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

#define Buffer_Limit 5
#define DATA_1 0
#define DATA_2 1

char buffer[Buffer_Limit];

int Buffer_In = 0;
int Buffer_Out = 0;
int data[2] = { -1, -1};


pthread_mutex_t mutex_variable = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t Buffer_Queue_Not_Full = PTHREAD_COND_INITIALIZER;
pthread_cond_t Buffer_Queue_Not_Empty = PTHREAD_COND_INITIALIZER;

void* Consumer_2(void* args){
	int* name = (int*) args;
	while(1){
		pthread_mutex_lock(&mutex_variable);
		if (Buffer_Out == Buffer_In)
		{
			pthread_cond_wait(&Buffer_Queue_Not_Empty, &mutex_variable); 
		}
		printf("Consumer: %c\n", buffer[Buffer_Out]);
		char ch = buffer[Buffer_Out];
		int num = ch - '0';
		
		 	
	 	if (data[DATA_1] != -1)
	 	{
	 		printf("sum = %d mul = %d\n", data[DATA_1] + data[DATA_2], data[DATA_1] * data[DATA_2]);
	 		data[0] = -1;
	 		data[1] = -1;
	 	} else {
	 		data[DATA_2] = num;
	 	}
		Buffer_Out = (Buffer_Out + 1) % Buffer_Limit;
		
		// 消费一个就可以唤醒
		pthread_cond_signal(&Buffer_Queue_Not_Full);
		//
		pthread_mutex_unlock(&mutex_variable);
	}
	return NULL;
}

void* Consumer_1(void* args){
	int* name = (int*) args;
	while(1){
		pthread_mutex_lock(&mutex_variable);
		if (Buffer_Out == Buffer_In)
		{
			pthread_cond_wait(&Buffer_Queue_Not_Empty, &mutex_variable); 
		}
		printf("Consumer: %c\n", buffer[Buffer_Out]);
		char ch = buffer[Buffer_Out];
		int num = ch - '0';
		
	 	if (data[DATA_2] != -1)
	 	{
	 		printf("sum = %d mul = %d\n", data[DATA_1] + data[DATA_2], data[DATA_1] * data[DATA_2]);
	 		data[0] = -1;
	 		data[1] = -1;
	 	} else {
	 		data[DATA_1] = num;
	 	}
		Buffer_Out = (Buffer_Out + 1) % Buffer_Limit;
		
		// 消费一个就可以唤醒
		pthread_cond_signal(&Buffer_Queue_Not_Full);
		//
		pthread_mutex_unlock(&mutex_variable);
	}
	return NULL;
}

void* Producer(void* args){
	char* filename = char* args;
	while(1){
		pthread_mutex_lock(&mutex_variable);
		if ((Buffer_In + 1) % Buffer_Limit == Buffer_Out)
		{
			// 满了就去阻塞 
			pthread_cond_wait(&Buffer_Queue_Not_Full, &mutex_variable);
		}
		FILE *source = fopen(filename, "r");
		char ch = fgetc(source);
		if (ch == EOF)
		{
			printf("%s 已读完\n", filename);
			break;
		}
		buffer[Buffer_In] = ch;
		printf("Producer:%d\n", Buffer_In);
		Buffer_In = (Buffer_In + 1) % Buffer_Limit;
		
		// 生产一个也去唤醒
		pthread_cond_signal(&Buffer_Queue_Not_Empty);
		pthread_mutex_unlock(&mutex_variable);
	}
	return NULL;	
}

int main(int argc, char const *argv[])
{
	pthread_t producer1_thread_id, consumer1_thread_id, producer2_thread_id, consumer2_thread_id;
	char file_1[] = "data1.txt";
	char file_2[] = "data2.txt";
	pthread_create(&producer1_thread_id, NULL, Producer, file_1);
	pthread_create(&producer2_thread_id, NULL, Producer, file_2);
	pthread_create(&consumer1_thread_id, NULL, Consumer_1, NULL);
	pthread_create(&consumer2_thread_id, NULL, Consumer_2, NULL);
	pthread_join(producer1_thread_id, NULL);
	pthread_join(producer2_thread_id, NULL);
	pthread_join(consumer1_thread_id, NULL);	
	pthread_join(consumer2_thread_id, NULL);
	return 0;
}