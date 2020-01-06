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
#define SIZE 100

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
// IPC_NOWAIT, который указывает на немедленный возврат из функции, если в очереди нет сообщений необходимого типа. При
// этом системный вызов возвращает ошибку, устанавливая значение errno равным ENOMSG;
// MSG_EXCEPT , который используется
// (если msgtyp больше, чем 0) для чтения первого сообщения, тип которого не равен msgtyp;
// MSG_NOERROR, используемый для
// урезания текста сообщения, размер которого больше msgsz байтов.
int main(int argc, char *argv[])
{
    key_t key;
    key = ftok(argv[0], 1); // получаем ключ для обращения к очереди сообщений
    perror("ftok");
    int msqid = msgget(key, IPC_CREAT | S_IRWXU); // создаем очередь с правами на чтение и запись
    perror("msgget");
    cout << "Очередь создана! Ключ: " << key << endl;
    cout << "Ожидается получение сообщений..." << endl;
    struct
    {
        long mtype;
        char mtext[SIZE];
    } rx, tx;

    while (1)
    {
        if (msgrcv(msqid, &rx, SIZE, 0, 0) == -1)
        {
            perror("msgrcv");
        }
        else
        {
            printf("[RECIEVE] Получено сообщение с ключом %d: %s\n", rx.mtype, rx.mtext);
        }
        int cqd;
        if ((cqd = msgget(rx.mtype, 0755)) == -1) // подключаемся к  очереди для отправки сообщения
        {
            perror("msgget (client queue)");
        }
        else
        {
            tx.mtype = 2;
            sprintf(tx.mtext, "%d", H(rx.mtext));
            if (msgsnd(cqd, &tx, SIZE, 0) == -1)
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