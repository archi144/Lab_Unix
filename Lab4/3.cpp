#include <cstring>
#include <iostream>
#include <sys/types.h>
#include <unistd.h>
#define SIZE 100
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
        char buf[SIZE]{"MSG FROM [P]"};
        write(filedes[1], buf, SIZE); // записываем в дескриптор для записи
        memset(buf, 0, SIZE);
        int n;
        do
        {
            n = read(filedes1[0], buf, SIZE);
            cout << "[P] получены данные: " << buf << endl;
            do
            {
                sleep(1);
                cout << "[P] Ответ дочернему процессу:" << endl;
                read(1, buf, SIZE);
                write(filedes[1], buf, SIZE);
            } while (false);
        } while (buf[0] != 'q');
        cout << "[P] Данные успешно получены" << endl;
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
        while (1)
        {
            sleep(1);
            cout << "[C] Ответ родительскому процессу:" << endl;
            read(1, buf, SIZE);
            write(filedes1[1], buf, SIZE);
            sleep(2);
            read(filedes[0], buf, SIZE);
            cout << "[C] получены данные: " << buf << endl;
        }

        close(filedes[0]);
        close(filedes1[1]);
    }
}