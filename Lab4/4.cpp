#include <cstring>
#include <iostream>
#include <sys/types.h>
#include <unistd.h>
#define SIZE 100
using namespace std;

int main(int argc, char *argv[])
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
        char buf[SIZE]{"MSG FROM [P]"};
        write(filedes[1], buf, SIZE); // записываем в дескриптор для записи
        while (read(filedes1[0], &buf, 1) > 0)
        {
            write(STDOUT_FILENO, &buf, 1);
        }
        cout << "\n[P] Данные успешно получены" << endl;
        close(filedes[1]);
        close(filedes1[0]);
    }
    else
    {
        close(filedes[1]);  // закрываем дескриптор для записи
        close(filedes1[0]); // закрываем дескриптор для чтения
        cout << "[С] Выполняется дочерний процесс PID = " << getpid() << endl;
        char buf[SIZE]{};
        read(filedes[0], buf, SIZE); // читаем из дескриптора для чтения
        cout << "[C] " << buf << endl;
        memset(buf, 0, SIZE);
        char str[3];
        sprintf(str, "%d", filedes1[1]);
        cout << "Отправляемый id pipe: " << str << endl;

        char *par[] = {"4ChildFile", str};
        argv[1] = "4ChildFile";
        argv[2] = str;

        execv(argv[1], argv + 1);
        write(filedes1[1], buf, SIZE);
        close(filedes[0]);
        close(filedes1[1]);
    }
}