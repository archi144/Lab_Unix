#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <sys/param.h>
#include <sys/stat.h>
#include <sys/user.h>
#include <sys/types.h>
#include <fcntl.h>
#include <errno.h>
#include <cstring>
#include <unistd.h>
#include <stddef.h>
#include <proc.h>
using namespace std;


int main(int argc,char* argv[])
{
	cout<<"\nРодительский PID: " << getpid()<< "\nРодительский PPID: "<< getppid()<< "\nРодительский GPID: "<< getgid() << endl;
	int status = fork();
	if(status)
	{
		cout<<"\nВыполняется родительский процесс..."<<endl;
		cout<<"\nВозвращаемый код fork: " << status << endl;
		cout<<"Родительский PID: " << getpid()<< "\nРодительский PPID: "<< getppid()<< "\nРодительский GPID: "<< getgid() << endl;
		pause();
	}
	else
	{
		cout<<"\nВыполняется дочерний процесс..."<<endl;
		cout<<"\nВозвращаемый код fork: " << status << endl;
		cout<<"Дочерний PID: " << getpid()<< "\nДочерний PPID: "<< getppid()<< "\nДочерний GPID: "<< getgid() << endl;
		pause();
	}
	cout<<"status : "<<status<<endl;
	return 0;
}
