#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <cstring>
#include <unistd.h>
#include <stddef.h>
using namespace std;


int main(int argc,char* argv[])
{
	extern char **environ;               // окружение 
	const char name[]{"MYNAME"};
	const char value[]{"ARTHUR"};
	setenv(name,value,1);                // установка значения переменной
	char var[]{"var = VAR"};
	putenv(var);                      // пуш переменной
	int i = 0;
	while(environ[i] != nullptr)
		{
			cout<<environ[i]<<endl;
			i++;
		}
	
	return 0;
}
