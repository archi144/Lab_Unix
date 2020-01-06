#include <errno.h>
#include <fcntl.h>
#include <iostream>
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

using namespace std;

int H(char *);
int main(int argc, char *argv[])
{
    printf("Шоу начинается!\n");
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
        char mtext[20];
    } rx, tx;
    int status = fork();
    if (status)
    {
        cout << "[P] Выполняется родительский процесс! PID " << getpid() << endl;
        sleep(2);
        strcpy(tx.mtext, "h");
        tx.mtype = 1; // отправляем ребенку
        msgsnd(qd, &tx, 20, 0);
        printf("[P] [SEND] Сообщение отправлено! (key = %ld; text = %s)\n", tx.mtype, tx.mtext);
        while (1)
        {
            if (msgrcv(qd, &rx, 24, 2, 0) == -1)
            {
                perror("msgrcv");
            }
            else
            {
                printf("[P] [RECIEVE] Получено сообщение с ключом %ld: %s\n", rx.mtype, rx.mtext);
                sleep(2);
                tx.mtype = 1;
                sprintf(tx.mtext, "%d", H(rx.mtext));
                if (msgsnd(qd, &tx, 24, 0) == -1)
                {
                    perror("msgsnd");
                }
                else
                {
                    printf("[P] [SEND] Ответ отправлен! (key = %ld; text = %s)\n", tx.mtype, tx.mtext);
                }
            }
        }
    }
    else
    {
        cout << "[C] Выполняется дочерний процесс! PID " << getpid() << endl;
        while (1)
        {
            if (msgrcv(qd, &rx, 24, 1, 0) == -1)
            {
                perror("msgrcv");
            }
            else
            {
                printf("[C] [RECIEVE] Получено сообщение с ключом %ld: %s\n", rx.mtype, rx.mtext);
                sleep(2);
                tx.mtype = 2;
                sprintf(tx.mtext, "%d", H(rx.mtext));
                if (msgsnd(qd, &tx, 24, 0) == -1)
                {
                    perror("msgsnd");
                }
                else
                {
                    printf("[C] [SEND] Ответ отправлен! (key = %ld; text = %s)\n", tx.mtype, tx.mtext);
                }
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