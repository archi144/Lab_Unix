#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <signal.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <math.h>

using namespace std;


void sighandler(int sig)
{
    cout<<"Hello world from "<<getpid()<<endl;
}


int main()
{
    struct sigaction act, oact;
    act.sa_handler = sighandler;
    sigaction(SIGUSR1, &act, &oact);
    sigset_t mask, omask;
    sigfillset(&mask);
    sigprocmask(SIG_SETMASK, &mask, &omask);
    sigdelset(&mask, SIGUSR1);   
  //  sigdelset(&mask, SIGINT);   
    sigprocmask(SIG_SETMASK, &mask, &omask); 
    int pid = getpid();
    int status = fork();
    if(status)
    {
        cout<<"Выполняется родительский процесс! " << "PID = "<<getpid()<<endl;
        sigsuspend(&mask);
        //cout<<sigpending(&mask)<<endl;
        sleep(1);
        kill(status, SIGUSR1);
        sigsuspend(&mask); 
        kill(status, SIGUSR1);
    }
    else{
        cout<<"Вполняется дочерний процесс! " << "PID = "<<getpid()<<endl;
        sleep(1);
        kill(pid, SIGUSR1);
        sigsuspend(&mask); 
        sleep(1);
        kill(pid, SIGUSR1);
        sigsuspend(&mask); 
         
    }
    return 0;
}

