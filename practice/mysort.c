#include <stdio.h>
#include <pthread.h>

int array[] = { 7, 12, 19, 3, 18, 4, 2, 6, 15, 8 };
int ret[10];

typedef struct{
    int first;
    int last;
    int isFinish;
}MY_ARGS;

void* sort(void* args){
    MY_ARGS* my_args = (MY_ARGS*)args;
    int first = my_args -> first;
    int last = my_args -> last;

 
    for(int i = first; i < last - 1; i++){
        for(int j = first; j + 1< last; j++){
            if(array[j] > array[j+1]){
                int temp = array[j];
                array[j] = array[j+1];
                array[j+1] = temp;
            }
        }       
    }    
  
    my_args -> isFinish = 1;
    return NULL;
}

void* merge_array(void* args){
    int l = 0;
    int h = 5;
    int i = 0;
    while(h < 10 && l < 5){
        if (array[l] > array[h])
        {
            ret[i++] = array[h];
            h++;
        } else {
            ret[i++] = array[l];
            l++;
        }
    }
    if (l < 5)
    {
        while(l < 5){
            ret[i++] = array[l++];
        }
    }
    if (h < 10)
    {
        while(h < 10){
            ret[i++] = array[h++];
        }
    }
    return NULL;
}

int main(){
    pthread_t sort_1;
    pthread_t sort_2;
    pthread_t merge;

    MY_ARGS arg_1 = { 0, 5, 0};
    MY_ARGS arg_2 = { 5, 10, 0};

    pthread_create(&sort_1, NULL, sort, &arg_1);
    pthread_create(&sort_2, NULL, sort, &arg_2);
    pthread_create(&merge, NULL, merge_array, NULL);

    pthread_join(sort_1, NULL);
    pthread_join(sort_2, NULL);
    pthread_join(merge, NULL);
      
    //for(int i = 0; i < 10; i++){
      //  printf("%d ", array[i]);
       // if (i == 4)
        //{
       //     printf(" ");
       // }
   // }
   // printf("\n");

    for (int i = 0; i < 10; ++i)
    {
        printf("%d ", ret[i]);
    }
    printf("\n");

    return 0;
}

