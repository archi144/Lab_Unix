#include <fcntl.h>
#include <iostream>
#include <sys/types.h>
#include <unistd.h>
#include <wait.h>
using namespace std;
int main(int argc, char *argv[])
{
    int status = fork();

    if (status)
    {
        cout << "[P] Выполняется родительский процесс PID = " << getpid() << endl;
        int fd = open(argv[1], O_WRONLY | O_CREAT, 0755);
        struct flock lock;
        lock.l_type = F_WRLCK;    // блокировка на чтение
        lock.l_start = 0;         // позиция блокировки в файле
        lock.l_whence = SEEK_SET; // смещение от начала
        lock.l_len = 0;           // блокировка до конца
        fcntl(fd, F_SETLKW, &lock);
        perror("");
        int i = 0;
        sleep(1);
        do
        {
            write(fd, "1", 1);
        } while (i++ < 100);

        close(fd);
        wait(0);
    }
    else
    {
        cout << "[С] Выполняется дочерний процесс PID = " << getpid() << endl;
        int fd = open(argv[1], O_RDONLY, 0755);

        struct flock lock;
        lock.l_type = F_RDLCK;    // блокировка на чтение
        lock.l_start = 0;         // позиция блокировки в файле
        lock.l_whence = SEEK_SET; // смещение от начала
        lock.l_len = 0;           // блокировка до конца
        fcntl(fd, F_SETLKW, lock);
        perror("");
        int i = 0;
        char c;
        do
        {
            read(fd, &c, 1);
            cout << c << " ";
        } while (i++ < 100);

        close(fd);
    }
}
