#include <iostream>
#include <sys/types.h>
#include <unistd.h>

using namespace std;
int main()
{
    int filedes[2];
    int filedes1[2];
    pipe(filedes);
    pipe(filedes1);
    /* создаем однонаправленный канал для обмена данными
     дескриптор для чтения filedes[0] и дескриптор для записи filedes[1] */
    int status = fork();

    if (status)
    {
        close(filedes[0]);  // закрываем дескриптор для чтения
        close(filedes1[1]); // закрываем дескриптор для записи
        cout << "[P] Выполняется родительский процесс PID = " << getpid() << endl;
        char buf[20]{"MSG FROM [P]"};
        write(filedes[1], buf, 20); // записываем в дескриптор для записи
        read(filedes1[0], buf, 20);
        cout << "[P] " << buf << endl;
        close(filedes[1]);
        close(filedes1[0]);
    }
    else
    {
        close(filedes[1]);  // закрываем дескриптор для записи
        close(filedes1[0]); // закрываем дескриптор для чтения
        cout << "[С] Выполняется дочерний процесс PID = " << getpid() << endl;
        char buf[20];
        read(filedes[0], buf, 20); // читаем из дескриптора для чтения
        cout << "[C] " << buf << endl;
        write(filedes1[1], "MSG FROM [C]", 15);
        close(filedes[0]);
        close(filedes1[1]);
    }
}