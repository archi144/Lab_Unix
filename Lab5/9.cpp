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

    key_t key, a_key;
    if ((key = ftok(*argv, 1)) == -1)
    {
        perror("ftok");
        exit(1);
    }

    if ((qd = msgget(key, IPC_CREAT | 0755)) == -1)
    {
        perror("msgget (rx)");
        exit(1);
    }
    else
    {
        printf("Очередь для приема сообщений создана! Ключ: %d\n", key);
    }

    if ((a_key = ftok(*argv, 2)) == -1)
    {
        perror("ftok");
        exit(1);
    }

    if ((cqd = msgget(a_key, IPC_CREAT | 0755)) == -1)
    {
        perror("msgget (tx)");
        exit(1);
    }
    else
    {
        printf("Очередь для отправки ответов создана! Ключ: %d\n", a_key);
    }

    printf("Ожидается получение сообщений...\n");
    struct
    {
        long mtype;
        char mtext[20];
    } rx, tx;

    while (1)
    {
        if (msgrcv(qd, &rx, 20, 0, 0) == -1)
        {
            perror("msgrcv");
        }
        else
        {
            printf("[RECIEVE] Получено сообщение с ключом %d: %s\n", rx.mtype, rx.mtext);
            tx.mtype = rx.mtype;
            sprintf(tx.mtext, "%d", H(rx.mtext));
            if (msgsnd(cqd, &tx, 20, 0) == -1)
            {
                perror("msgsnd");
            }
            else
            {
                printf("[SEND] Ответ отправлен! (key = %d, text = %s)\n", tx.mtype, tx.mtext);
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