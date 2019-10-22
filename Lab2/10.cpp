#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <errno.h>
#include <cstring>
#include <unistd.h>
#include <stddef.h>
using namespace std;


int main(int argc, char* argv[])
{
	extern char **environ;
	int i = 0;
	cout << "\nРодительский PID: " << getpid() << "\nРодительский PPID: " << getppid() << "\nРодительский GPID: " << getgid() << endl;
	int status = fork();
	if (status)
	{
		cout << "\nВыполняется родительский процесс..." << endl;
		cout << "\nВозвращаемый код fork: " << status << endl;
		cout << "Родительский PID: " << getpid() << "\nРодительский PPID: " << getppid() << "\nРодительский GPID: " << getgid() << endl;
		cout << "Параметры родителя:" << endl;
		for (int i = 1; argv[i] != nullptr; i++)
		{
			cout<<argv[i]<<endl;
		}
		        cout << "Окружение родителя: " << endl;
		        while (environ[i] != nullptr)
		{
			cout << environ[i] << endl;
				i++;
			}
	}
	else
	{

		cout << "\nВыполняется дочерний процесс..." << endl;
		execvp(argv[1], (argv + 2));
		cout << "\nВозвращаемый код fork: " << status << endl;
		cout << "Дочерний PID: " << getpid() << "\nДочерний PPID: " << getppid() << "\nДочерний GPID: " << getgid() << endl;
		cout << "Параметры дочери:" << endl;
		for (int i = 1; argv[i] != nullptr; i++)
		{
			cout<<argv[i]<<endl;
		}
		cout << "Окружение дочери: " << endl;
		while (environ[i] != nullptr)
		{
			cout << environ[i] << endl;
			i++;
		}
	}
	cout << "status : " << status << endl;


	return 0;
}

