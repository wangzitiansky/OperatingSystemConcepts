#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

#define Buffer_Limit 10

int Buffer_Index_Value = 0;
char* Buffer_Queue;

pthread_mutex_t mutex_variable = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t Buffer_Queue_Not_Full = PTHREAD_COND_INITIALIZER;
pthread_cond_t Buffer_Queue_Not_Empty = PTHREAD_COND_INITIALIZER;

void* Consumer(){
	while(1){
		pthread_mutex_lock(&mutex_variable);
		if (Buffer_Index_Value == -1)
		{
			// 空了也阻塞
			pthread_cond_wait(&Buffer_Queue_Not_Empty, &mutex_variable);
			// 阻塞 直到特定的condition被激活 并且unlock mutex
		}
		printf("Consumer: %d\t", Buffer_Index_Value--);
		
		// 消费一个就可以唤醒
		pthread_cond_signal(&Buffer_Queue_Not_Empty);
		//
		pthread_mutex_unlock(&mutex_variable);
	}
}

void* Producer(){
	while(1){
		pthread_mutex_lock(&mutex_variable);
		if (Buffer_Index_Valu == Buffer_Limit)
		{
			// 满了就去阻塞 
			pthread_cond_wait(&Buffer_Queue_Not_Full, &mutex_variable);
		}
		Buffer_Queue[Buffer_Index_Value++] = '@';
		printf("Producer:%d\t", Buffer_Index_Value);
		// 生产一个也去唤醒
		pthread_cond_signal(&Buffer_Queue_Not_Empty);
		pthread_mutex_unlock(&mutex_variable);
	}	
}

int main(int argc, char const *argv[])
{
	pthread_t producer_thread_id, consumer_thread_id;
	Buffer_Queue = (char*)malloc(sizeof(char)*Buffer_Limit);
	pthread_create(&producer_thread_id, NULL, Producer, NULL);
	pthread_create(&consumer_thread_id, NULL, Consumer, NULL);
	pthread_join(producer_thread_id, NULL);
	pthread_join(consumer_thread_id, NULL);
	return 0;
}