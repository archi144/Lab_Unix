#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <sys/param.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <sys/user.h>
#include <sys/types.h>
#include <fcntl.h>
#include <errno.h>
#include <cstring>
#include <unistd.h>
using namespace std;


int main(int argc,char* argv[])
{
	cout<<"\nРодительский PID: " << getpid()<< "\nРодительский PPID: "<< getppid()<< "\nРодительский GPID: "<< getgid() << endl;
	int status = fork();
	if(status)
	{
		int fd = open(argv[1],O_RDWR);
		cout<<"\nВыполняется родительский процесс..."<<endl;
		int Pfd = creat("Parent_file",00700);
		char buf[5000]{};
		int len = read(fd,buf,5000);
		write(Pfd,buf,len);
		wait(&status);
		read(Pfd,buf,len);
		cout<<"Содержимое родительского файла:\n"<<buf<<endl;
	}
	else
	{
		int fd = open(argv[1],O_RDWR);
		cout<<"\nВыполняется дочерний процесс..."<<endl;
		int Cfd = creat("Child_file",00700);
		char buff[5000]{};
		int lent = read(fd,buff,5000);
		write(Cfd,buff,lent);
		read(Cfd,buff,lent);
		cout<<"Содержимое дочернего файла:\n"<<buff<<endl;
	}
	cout<<"status : "<<status<<endl;
	return 0;
}
