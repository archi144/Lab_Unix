#include <errno.h>
#include <fcntl.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
int H(char *);
int main(int argc, char *argv[])
{
    printf("Server started!\n");
    int qd, cqd;
    key_t key;
    if ((key = ftok(*argv, 1)) == -1)
    {
        perror("ftok");
        exit(1);
    }
    if ((qd = msgget(key, IPC_CREAT | 0755)) == -1)
    {
        perror("msgget");
        exit(1);
    }
    else
    {
        printf("Очередь создана! Ключ: %d\n", key);
    }

    printf("Ожидается получение сообщений...\n");
    struct
    {
        long mtype;
        int sender;
        char mtext[20];
    } rx, tx;

    while (1)
    {
        if (msgrcv(qd, &rx, 24, 1, 0) == -1)
        {
            perror("msgrcv");
        }
        else
        {
            printf("[RECIEVE] Получено сообщение с ключом %ld (sender = %d): %s\n", rx.mtype, rx.sender, rx.mtext);
            tx.mtype = rx.sender;
            tx.sender = 1;
            sprintf(tx.mtext, "%d", H(rx.mtext));
            if (msgsnd(qd, &tx, 24, 0) == -1)
            {
                perror("msgsnd");
            }
            else
            {
                printf("[SEND] Ответ отправлен! (key = %ld; sender = %d; text = %s)\n", tx.mtype, tx.sender, tx.mtext);
            }
        }
    }
}

int H(char *str)
{
    int result = 0;
    int i = 0;
    do
    {
        result ^= *(str + i);
    } while (*(str + (++i)));
    return result;
}