#include <errno.h>
#include <iostream>
#include <signal.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
using namespace std;
int i = 0;
void func(int d)
{
    cout << "Hello world!" << endl;
    i = 8;
}

int main()
{
    int status = 0;
    int killStat;
    if (status)
    {
        // sleep(15);
        // killStat = kill(status, SIGINT);

        wait(&status);
        cout << "WIFEXITED - " << WIFEXITED(status) << endl // не равно нулю если процесс удачно завершился
             << "WIFSIGNALED - " << WIFSIGNALED(status)
             << endl // возвращает true если   дочерний   процесс   завершился
             // из-за неперехваченного сигнала.
             << "WTERMSIG - " << WTERMSIG(status) << endl; // возвращает номер сигнала из-за которого был завершён
                                                           // дочерний процесс
    }
    else
    {
        sleep(1);
        cout << "Started" << endl;
        signal(SIGINT, func); // переопределяем реакцию на сигнал SIGINT

        for (; i < 10; i++)
        {
            cout << i << endl;
            for (int k = 0; k < 10000; k++)
            {
                for (int j = 0; j < 1000000; j++)
                {
                }
            }
        }
    }
    cout << "Возвращенный код от дочернего процесса : " << status << endl;
    cout << "Kill завершился с кодом: " << killStat << endl;
    return 0;
}
