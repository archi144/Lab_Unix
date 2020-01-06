#include <cstring>
#include <errno.h>
#include <fcntl.h>
#include <iostream>
#include <mqueue.h>
#include <signal.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/types.h>
#include <unistd.h>
#define SIZE 30

using namespace std;

int get_stats(int qd);

struct msgbuff
{
    long mtype;
    char mtext[SIZE];
    msgbuff(const char text[], long msgtype)
    {
        strcpy(this->mtext, text);
        this->mtype = msgtype;
    }
    msgbuff()
    {
    }
};
// IPC_NOWAIT, который указывает на немедленный возврат из функции, если в очереди нет сообщений необходимого типа. При
// этом системный вызов возвращает ошибку, устанавливая значение errno равным ENOMSG;
// MSG_EXCEPT , который используется
// (если msgtyp больше, чем 0) для чтения первого сообщения, тип которого не равен msgtyp;
// MSG_NOERROR, используемый для
// урезания текста сообщения, размер которого больше msgsz байтов.
int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        printf("Используйте: %s <server filename>\n", *argv);
        exit(1);
    }
    printf("Клиент запущен!\n");
    key_t srv_key, key;
    if ((srv_key = ftok(*(argv + 1), 1)) == -1) // создаем такой же ключ, как и у сервера
    {
        perror("ftok (srv)");
        exit(1);
    }
    int qd, pqd;
    if ((pqd = msgget(srv_key, 0755)) == -1) // на основе созданного выше ключа открываем канал сообщений
    {
        perror("msgget (srv queue)");
        exit(1);
    }
    printf("Соедиение с очередью сервера (%d) установлено!\n", srv_key);
    if ((key = ftok(*argv, getpid())) == -1) // создаем ключ из дескриптора собственного файла
    {
        perror("ftok (client)");
        exit(0);
    }
    if ((qd = msgget(key, IPC_CREAT | 0755)) == -1) // создаем канал сообщений по собственному ключу
    {
        perror("msgget (client queue)");
        exit(1);
    }
    printf("Очередь с ключом %d создана!\n", key);
    struct
    {
        long mtype;
        char mtext[SIZE];
    } tx, rx;

    while (1)
    {
        printf("Введите сообщение: ");
        cin >> tx.mtext;
        tx.mtype = key;                    // вшиваем ключ в тип сообщения
        if (msgsnd(pqd, &tx, 20, 0) == -1) // отправляем серверу сообщение
        {
            perror("msgsnd");
        }
        else
        {
            printf("Сообщение отправлено! Ожидание ответа...\n");
        }

        if (msgrcv(qd, &rx, 20, 2, MSG_NOERROR) == -1)
        {
            perror("msgrcv");
        }
        else
        {
            printf("Получен ответ! (key = %d ; text = %s)\n", rx.mtype, rx.mtext);
        }
    }
}

int get_stats(int qd)
{
    struct msqid_ds qds;
    if (msgctl(qd, IPC_STAT, &qds) == -1)
        perror("");
    cout << "UserID = " << qds.msg_perm.uid << endl;
    cout << "GroupID = " << qds.msg_perm.gid << endl;
    cout << "Права доступа: " << qds.msg_perm.mode << endl;
    cout << "Макс кол-во байт для записи = " << qds.msg_qbytes << endl;
    cout << "Кол-во сообщений: " << qds.msg_qnum << endl;
    cout << "PID последнего отправителя: " << qds.msg_lspid << endl;
    cout << "PID последнего получателя: " << qds.msg_lrpid << endl;
    return 0;
}