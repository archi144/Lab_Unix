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
	cout<<"Текущий PID: " << getppid()<< " Текущий PPID: "<< getppid()<< " Текущий GPID: "<< getgid() << endl;
	int status=fork();
	if(status)
	{
		cout<<"\nВыполняется родительский процесс..."<<endl;
		cout<<"\nВозвращаемый код fork: " << status << endl;
		cout<<"Родительский PID: " << getpid()<< "\nРодительский PPID: "<< getppid()<< "\nРодительский GPID: "<< getgid() << endl;
		wait(&status);
		cout<<"Статус ожидания: " <<WIFEXITED(status)<<endl;    //не равно нулю, если дочерний процесс успешно завершился.
	}
	else
	{
		cout<<"\nВыполняется дочерний процесс..."<<endl;
		cout<<"\nВозвращаемый код fork: " << status << endl;
		cout<<"Дочерний PID: " << getpid()<< "\nДочерний PPID: "<< getppid()<< "\nДочерний GPID: "<< getgid() << endl;

	}
	return 0;
}
