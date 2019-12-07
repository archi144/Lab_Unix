#include <iostream>
#include <sys/types.h>
#include <unistd.h>

using namespace std;
int main()
{
    int filedes[2];
    pipe(filedes);
    /* создаем однонаправленный канал для обмена данными
     дескриптор для чтения filedes[0] и дескриптор для записи filedes[1] */
    int status = fork();

    if (status)
    {
        close(filedes[0]); // закрываем дескриптор для чтения
        cout << "[P] Выполняется родительский процесс PID = " << getpid() << endl;
        char buf[20]{"MSG FROM [P]"};
        write(filedes[1], buf, 20); // записываем в дескриптор для записи
    }
    else
    {
        close(filedes[1]); // закрываем дескриптор для записи
        cout << "[С] Выполняется дочерний процесс PID = " << getpid() << endl;
        char buf[20];
        read(filedes[0], buf, 20); // читаем из дескриптора для чтения
        cout << "[C] " << buf << endl;
    }
}