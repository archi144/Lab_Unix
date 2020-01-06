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
#include <time.h>
#include <unistd.h>

using namespace std;

void signal_handler(int);
key_t key;

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        printf("Usage: %s <server_filename>\n", *argv);
        exit(1);
    }
    printf("Client started!\n");

    struct sigaction act, oact;
    act.sa_handler = signal_handler;
    act.sa_flags = SA_RESETHAND;
    if (sigaction(SIGINT, &act, &oact) == -1)
    {
        perror("sigaction");
    }
    key_t srv_key;
    if ((srv_key = ftok(*(argv + 1), 1)) == -1)
    {
        perror("ftok");
        exit(1);
    }
    int qd, pqd;
    if ((pqd = msgget(srv_key, 0755)) == -1)
    {
        perror("msgget (srv queue)");
        exit(1);
    }
    printf("Соедиение с очередью сервера (%d) установлено!\n", srv_key);
    if ((key = ftok(*argv, 1)) == -1)
    {
        perror("ftok");
        exit(1);
    }
    if ((qd = msgget(key, IPC_CREAT | 0755)) == -1)
    {
        perror("msgget (client queue)");
        exit(1);
    }
    printf("Очередь с ключом %d создана!\n", key);
    struct
    {
        long mtype;
        char mtext[20];
    } tx, rx;

    while (1)
    {
        printf("Введите сообщение: ");
        cin >> tx.mtext;
        tx.mtype = key;
        if (msgsnd(pqd, &tx, 20, 0) == -1)
        {
            perror("msgsnd");
        }
        else
        {
            printf("Сообщение отправлено! Ожидание ответа...\n");
        }

        if (msgrcv(qd, &rx, 20, 0, 0) == -1)
        {
            perror("msgrcv");
        }
        else
        {
            printf("Получен ответ! (key = %d ; text = %s)\n", rx.mtype, rx.mtext);
        }
    }
}

void signal_handler(int sig)
{
    if (sig == SIGINT)
    {
        int qd;
        if ((qd = msgget(key, 0755)) == -1)
        {
            perror("[HND] msgget");
        }
        else
        {
            if (msgctl(qd, IPC_RMID, NULL) == -1)
            {
                perror("[HND] msgctl");
            }
            else
            {
                printf("[HND] Очередь %d уничтожена!\n", key);
                exit(0);
            }
        }
    }
}