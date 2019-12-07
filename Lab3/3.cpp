#include <iostream>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
using namespace std;

int main(int argc, char *argv[])
{
    int status = fork();
    if (status)
    {
        struct sigaction act;
        act.sa_flags = SA_NOCLDWAIT;
        cout << "\nВыполняется родительский процесс..." << endl;
        cout << "\nВозвращаемый код fork: " << status << endl;
        cout << "Родительский PID: " << getpid() << "\nРодительский PPID: " << getppid()
             << "\nРодительский GPID: " << getgid() << endl;
        // signal(SIGCHLD,SIG_DFL);
        sigaction(SIGCHLD, &act, 0);
        pause();
    }
    else
    {

        cout << "\nВыполняется дочерний процесс..." << endl;
        cout << "\nВозвращаемый код fork: " << status << endl;
        cout << "Дочерний PID: " << getpid() << "\nДочерний PPID: " << getppid() << "\nДочерний GPID: " << getgid()
             << endl;
        exit(0);
    }
    cout << "status : " << status << endl;
    return 0;
}
