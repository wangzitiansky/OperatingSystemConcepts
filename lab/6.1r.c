#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>


#define SERVER_KEY_PATHNAME "key"
#define PROJECT_ID 'M'
#define QUEUE_PERMISSIONS 0666
#define MAXSIZE 1024
#define NUM_SEND 10



struct message {
    long type;
    char text[MAXSIZE];
};

int main (int argc, char **argv)
{
   key_t key;
   long qid;
   size_t n;
   struct message m;
   int result;
   
   key = 168;

   qid = msgget(key, IPC_CREAT | 0666);
   if (qid < 0)
   {
        perror("can not msgget");
        exit(1);
   }

   for (int i = 0; i < NUM_SEND; ++i)
   {
       printf("接受第%d条\n", i+1);
       result = msgrcv(qid, &m, MAXSIZE-1, 0, 0);
       printf("get %d bytes\n", result);
       if (result < 0)
       {
           perror("msgrcv");
           exit(1);
       }
       printf("%s\n", m.text);
   }

  if(msgctl(qid, IPC_RMID, NULL) == -1){
    perror("删除消息队列失败");    
  }

}