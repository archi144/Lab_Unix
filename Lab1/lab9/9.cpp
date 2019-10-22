#include <iostream>
#include <stdio.h>
#include <string>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <cstring>

#define ALL 0000700
#define READ 0000400
#define WRITE 0000200
#define EXEC 0000100
#define SIZE 512
using namespace std;


int copy()
{
	int strLength;
	char buf[SIZE];
	strLength = read(0, buf, SIZE);
	write(1, buf, strLength);
	return 0;
}

int main(int argc, char* argv[])
{
	int copyFrom;
	int copyTo;
	char cFname[10] {};
	char cTname[10] {};
	if (argv[1] == nullptr && argv[2] == nullptr)
	{
		cout << "Пожалуйста, введите название файлов через пробел:" << endl;
		cin >> cFname >> cTname;
		copyFrom = open(cFname, O_RDONLY);
		copyTo = open(cTname, O_WRONLY);
		dup2(copyFrom, 0);        // связываем поток ввода с первым файлом
		dup2(copyTo, 1);		  // связываем поток вывода со вторым файлом
		copy();
		close(copyFrom);
		close(copyTo);
	}
	else
	{
		copyFrom = open(argv[1], O_RDONLY);
		copyTo = open(argv[2], O_WRONLY);
		dup2(copyFrom, 0);
		dup2(copyTo, 1);
		copy();
		close(copyFrom);
		close(copyTo);
	}
	return 0;
}
