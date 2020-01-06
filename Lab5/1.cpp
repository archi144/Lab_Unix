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
int main()
{
    int msqid = msgget(IPC_PRIVATE, S_IRWXU); // создаем очередь с правами на чтение и запись
    perror("msgget");

    msgbuff message{"Hello world", 1}; // создаем сообщение с параметрами {текст, тип сообщения}
    msgbuff message1{"Hello world2", 2};
    msgbuff message2{"Hello world3", 3};

    msgbuff recieveMsg; // создаем сообщение, в которое считаем ранее отправленное сообщение
    msgbuff recieveMsg1;
    msgbuff recieveMsg2;

    msgsnd(msqid, &message, SIZE, IPC_NOWAIT);  // отправляем сообщение
    msgsnd(msqid, &message1, SIZE, IPC_NOWAIT); // отправляем сообщение
    msgsnd(msqid, &message2, SIZE, IPC_NOWAIT); // отправляем сообщение

    get_stats(msqid);
    perror("msgsnd");

    msgrcv(msqid, &recieveMsg, SIZE, 1, IPC_NOWAIT);  // получаем сообщение с типом "1"
    msgrcv(msqid, &recieveMsg1, SIZE, 2, IPC_NOWAIT); // получаем сообщение с типом "2"
    msgrcv(msqid, &recieveMsg2, SIZE, 3, IPC_NOWAIT); // получаем сообщение с типом "3"
    perror("msgrcv");

    cout << "Полученные сообщения: \n"
         << recieveMsg.mtext << endl
         << recieveMsg1.mtext << endl
         << recieveMsg2.mtext << endl;
    get_stats(msqid);
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