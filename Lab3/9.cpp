#include <errno.h>
#include <iostream>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
using namespace std;

void func(int i)
{
    cout << "Hello world!" << endl;
}

int main(int argc, char *argv[])
{
    int status = fork();
    int killStat;
    if (status)
    {
        sleep(2);
        killStat = kill(status, SIGALRM);
        wait(&status);
        cout << "WIFEXITED - " << WIFEXITED(status) << endl // не равно нулю если процесс удачно завершился
             << "WIFSIGNALED - " << WIFSIGNALED(status)
             << endl // возвращает true если   дочерний   процесс   завершился   из-за неперехваченного сигнала.
             << "WTERMSIG - " << WTERMSIG(status)
             << endl; // возвращает номер сигнала из-за которого был завершён  дочерний процесс
    }
    else
    {
        sleep(1);
        signal(SIGALRM, func); // переопределяем реакцию на сигнал alarm
        alarm(2);              // ставим будильник на две секунды
        for (int i = 0; i < 100; i++)
        {
            cout << i;
            for (int k = 0; k < 10000000; k++)
            {
            }
        }
    }
    cout << "Возвращенный код от дочернего процесса : " << status << endl;
    cout << "Kill завершился с кодом: " << killStat << endl;
    return 0;
}
