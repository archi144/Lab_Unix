#include <errno.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <termios.h>
#include <unistd.h>

using namespace std;

int main(int argc, char *argv[])
{

    int pid;
    if ((pid = fork()) == -1)
    {
        perror("fork error");
        exit(1);
    }

    char buf[100];
    if (pid)
    {
        cout << "[P] Выполняется родительский процесс PID = " << getpid() << endl;
        int n;
        while (1)
        {
            if ((n = read(0, &buf, sizeof(buf))) == -1)
            {
                perror("[P] ошибка чтения");
            }
            write(1, "[P] ", 4);
            if (write(1, buf, n) == -1)
            {
                perror("[P] ошибка записи");
            }
        }
    }
    else
    {
        cout << "[С] Выполняется дочерний процесс PID = " << getpid() << endl;
        int n;
        while (1)
        {
            if ((n = read(0, &buf, sizeof(buf))) == -1)
            {
                perror("[C] ошибка чтения");
            }
            write(1, "[C] ", 4);
            if (write(1, buf, n) == -1)
            {
                perror("[C] ошибка записи");
            }
        }
    }
    return 0;
}