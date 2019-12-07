#include <errno.h>
#include <fcntl.h>
#include <iostream>
#include <signal.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

using namespace std;

void func(int)
{
    cout << "Hello world!" << endl;
}

int main()
{
    struct sigaction act, oact; // структуры для хранения параметров сигнала
    sigset_t set, oset;         // наборы сигналов

    act.sa_handler = func; // задаем свой обработчик сигнала

    /* переопределяем обработчики сигналов на свой обработчик */
    sigaction(SIGUSR1, &act, &oact);

    sigaction(SIGUSR2, &act, &oact);

    sigaction(SIGALRM, &act, &oact);

    sigaction(SIGCONT, &act, &oact);

    sigaction(SIGINT, &act, &oact);

    sigfillset(&set); // запонляем set всеми сигналами

    sigdelset(&set, SIGUSR1); // удаляем из set SIGUSR1

    cout << "Sigismember - " << sigismember(&set, SIGUSR1) << endl;

    sigprocmask(SIG_SETMASK, &set, &oset); // устанавливаем маску блокируемых сигналов set для процесса

    kill(getpid(), SIGUSR1);

    kill(getpid(), SIGUSR1);

    kill(getpid(), SIGUSR1);

    kill(getpid(), SIGUSR1);

    sigprocmask(SIG_SETMASK, &oset, 0);

    return 0;
}
