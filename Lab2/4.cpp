#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <sys/param.h>
#include <sys/stat.h>
#include <sys/user.h>
#include <sys/user.h>
#include <fcntl.h>
#include <wait.h>
#include <errno.h>
#include <cstring>
#include <unistd.h>
#include <stddef.h>
using namespace std;


int main(int argc,char* argv[])
{
	pid_t ParentPID = getppid();
	pid_t ParentPPID = getppid();
	pid_t ParentGID = getppid();

	cout<<"Родительский PID: " << getpid()<< " Родительский PPID: "<< getppid()<< " Родительский GID: "<< getgid() << endl;
	cout<<"Наследуем через функцию fork...\n";
	int pid=fork();
	cout<<"Возвращаемое значение fork: " << pid << endl;
	int status;
	status = kill(ParentPID,0);
	cout<<"Код убийства завершился со статусом: " << status<< endl;
	cout<<"Текущий PID: " << getpid()<< " Текущий PPID: "<< getppid()<< " Текущий GPID: "<< getpid() << endl;	
	return 0;
}
