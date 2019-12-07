#include <iostream>
#include <sys/types.h>
#include <unistd.h>

using namespace std;
int main(int argc, char *argv[])
{
    int filedes[2];
    pipe(filedes);
    /* создаем однонаправленный канал для обмена данными
     дескриптор для чтения filedes[0] и дескриптор для записи filedes[1] */
    int ReadChan = filedes[0];
    int WriteChan = filedes[1];
    int status = fork();

    if (status)
    {
        close(filedes[0]);
        close(STDOUT_FILENO);
        cout << "[P] Выполняется родительский процесс PID = " << getpid() << endl;
        dup2(WriteChan, STDOUT_FILENO);
        execvp("/usr/bin/who", argv);
    }
    else
    {
        close(filedes[1]);
        close(STDIN_FILENO);
        cout << "[С] Выполняется дочерний процесс PID = " << getpid() << endl;
        dup2(ReadChan, STDIN_FILENO);
        char *buf[] = {"/usr/bin/wc", "-l", NULL};
        execvp(buf[0], buf);
    }
}