#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>
int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        printf("Usage: %s <server_filename>\n", *argv);
        exit(1);
    }
    printf("Клиент начал свою работу!\n");
    key_t srv_key;
    if ((srv_key = ftok(*(argv + 1), 1)) == -1)
    {
        perror("ftok");
        exit(1);
    }
    int qd;
    if ((qd = msgget(srv_key, 0755)) == -1)
    {
        perror("msgget (srv queue)");
        exit(1);
    }
    printf("Соедиение с очередью сервера (%d) установлено!\n", srv_key);
    struct
    {
        long mtype;
        int sender;
        char mtext[20];
    } tx, rx;

    while (1)
    {
        printf("Введите сообщение: ");
        scanf("%s", tx.mtext);
        tx.mtype = 1;
        tx.sender = getpid();
        if (msgsnd(qd, &tx, 24, 0) == -1)
        {
            perror("msgsnd");
        }
        else
        {
            printf("Сообщение отправлено! Ожидание ответа...\n");
        }

        if (msgrcv(qd, &rx, 24, getpid(), 0) == -1)
        {
            perror("msgrcv");
        }
        else
        {
            printf("Получен ответ! (key = %ld; sender = %d; text = %s)\n", rx.mtype, rx.sender, rx.mtext);
        }
    }
}