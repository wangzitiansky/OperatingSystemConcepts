#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

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
    struct message m;

    key = 168;

    if ((qid = msgget (key, IPC_CREAT | 0666)) == -1) {
        perror ("msgget: myqid");
        exit (1);
    }

    for (int i = 0; i < NUM_SEND; ++i)
    {
        printf("输入第%d条消息:\n", i+1);
        fgets(m.text, MAXSIZE, stdin);
        m.type = 1;
        int ret = msgsnd(qid, &m, strlen(m.text), 0);
        if (ret< 0)
        {
            perror("erro in send");
            exit(1);
        } else {
            printf("sended\n");
        }
    }
    return 0;
    
}