#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

int s = 0;

void* myfunc(void* args){
    for(int i = 0; i < 10000; i++){
        s = s + 1;
    }
    return NULL;
}


int main(){
    /*
    for(int i = 0; i < 5000; i++){
        arr[i] = rand() % 50;
    }
    */
    pthread_t th1;
    pthread_t th2;
    
    pthread_create(&th1, NULL, myfunc, NULL);
    pthread_create(&th2, NULL, myfunc, NULL);

    pthread_join(th1, NULL);
    pthread_join(th2, NULL);

    printf("s = %d\n", s);
    return 0;
}
