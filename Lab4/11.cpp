#include <errno.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/file.h>
#include <sys/types.h>
#include <termios.h>
#include <unistd.h>

using namespace std;

int main(int argc, char *argv[])
{

    int pid;
    if ((pid = fork()) == -1)
    {
        perror("Ошибка наследования");
        exit(1);
    }

    char buf[100];
    struct flock wl, rl;
    if (pid)
    {
        cout << "[P] Выполняется родительский процесс PID = " << getpid() << endl;
        int n;
        wl.l_type = F_WRLCK;
        wl.l_whence = SEEK_CUR;
        wl.l_start = 0;
        wl.l_len = 0;
        rl.l_type = F_RDLCK;
        rl.l_whence = SEEK_CUR;
        rl.l_start = 0;
        rl.l_len = 0;

        while (1)
        {
            wl.l_type = F_WRLCK;
            rl.l_type = F_RDLCK;
            fcntl(0, F_SETLKW, &rl);
            fcntl(1, F_SETLKW, &wl);
            if ((n = read(0, &buf, sizeof(buf))) == -1)
            {
                perror("[P] ошибка чтения");
            }
            write(1, "[P] ", 4);
            if (write(1, buf, n) == -1)
            {
                perror("[P] ошибка записи");
            }
            wl.l_type = F_UNLCK;
            rl.l_type = F_UNLCK;
            fcntl(0, F_SETLK, &rl);
            fcntl(1, F_SETLK, &wl);
        }
    }
    else
    {
        cout << "[С] Выполняется дочерний процесс PID = " << getpid() << endl;
        wl.l_type = F_WRLCK;
        wl.l_whence = SEEK_CUR;
        wl.l_start = 0;
        wl.l_len = 0;
        rl.l_type = F_RDLCK;
        rl.l_whence = SEEK_CUR;
        rl.l_start = 0;
        rl.l_len = 0;

        int n;
        while (1)
        {
            wl.l_type = F_WRLCK;
            rl.l_type = F_RDLCK;
            fcntl(0, F_SETLKW, &rl);
            fcntl(1, F_SETLKW, &wl);
            if ((n = read(0, &buf, sizeof(buf))) == -1)
            {
                perror("ошибка чтения");
            }
            write(1, "[C] ", 4);
            if (write(1, buf, n) == -1)
            {
                perror("ошибка записи");
            }
            // unlock
            wl.l_type = F_UNLCK;
            rl.l_type = F_UNLCK;
            fcntl(0, F_SETLK, &rl);
            fcntl(1, F_SETLK, &wl);
        }
    }
    return 0;
}
