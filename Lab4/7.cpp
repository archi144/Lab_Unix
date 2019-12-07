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
        int i = 0;

        char c;
        do
        {
            read(fd, &c, 1);
            cout << c << " " << endl;

        } while (i++ < 100);

        close(fd);
    }
}