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
    if (argc < 3)
    {
        cout << "Задайте параметры: id очереди, тип сообщения" << endl;
        exit(1);
    }
    int msg_type = strtol(argv[2], NULL, 10); // преобразовываем параметр командной строки в тип long
    key_t key;
    key = ftok(argv[1], 1); // получаем ключ для обращения к очереди сообщений
    perror("ftok");
    int msqid = msgget(key, IPC_CREAT | S_IRWXU); // открываем очередь с правами на чтение и запись
    perror("msgget");

    msgbuff message{"Hello world", msg_type}; // создаем сообщение с параметрами {текст, тип сообщения}
    msgbuff recieveMsg; // создаем сообщение, в которое считаем ранее отправленное сообщение
    msgsnd(msqid, &message, SIZE, IPC_NOWAIT); // отправляем сообщение
    perror("msgsnd");

    msgrcv(msqid, &recieveMsg, 5, msg_type, IPC_NOWAIT | MSG_NOERROR); // получаем сообщение с типом "1"
    perror("msgrcv");

    cout << "Полученные сообщения: \n" << recieveMsg.mtext << endl;
    return 0;
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