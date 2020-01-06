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
    printf("Client started!\n");
    key_t tx_key, rx_key;
    int qd, pqd;
    if ((tx_key = ftok(*(argv + 1), 1)) == -1)
    {
        perror("ftok (tx)");
        exit(1);
    }
    if ((rx_key = ftok(*(argv + 1), 2)) == -1)
    {
        perror("ftok (rx)");
        exit(1);
    }

    if ((pqd = msgget(tx_key, 0755)) == -1)
    {
        perror("msgget (srv queue)");
        exit(1);
    }
    printf("Соедиение с очередью сервера (%d) установлено!\n", tx_key);
    if ((qd = msgget(rx_key, IPC_CREAT | 0755)) == -1)
    {
        perror("msgget (client queue)");
        exit(1);
    }
    printf("Соединение с очередью сервера для получения ответов (%d) установлено!\n", rx_key);

    struct
    {
        long mtype;
        char mtext[20];
    } tx, rx;

    while (1)
    {
        printf("Введите сообщение: ");
        scanf("%s", tx.mtext);
        tx.mtype = getpid();
        if (msgsnd(pqd, &tx, 20, 0) == -1)
        {
            perror("msgsnd");
        }
        else
        {
            printf("Сообщение отправлено! Ожидание ответа...\n");
        }

        if (msgrcv(qd, &rx, 20, getpid(), 0) == -1)
        {
            perror("msgrcv");
        }
        else
        {
            printf("Получен ответ! (key = %ld ; text = %s)\n", rx.mtype, rx.mtext);
        }
    }
}