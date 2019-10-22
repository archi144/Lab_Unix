#include <iostream>
#include <ctime>
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
using namespace std;



int main(int argc, char* argv[])
{
	int file;					// дескриптор файла
	if (argv[1] == nullptr)
	{
		char name[10];
		cout << "Введите имя файла: ";
		cin >> name;
		
		file = open(name, O_RDONLY);
		int end = lseek(file, 0, SEEK_END);   // определям конец файла
		
		while (end--)
		{
			lseek(file, end, SEEK_SET);
			char buff[1];
			read(file, buff, 1);
			cout << buff[0];
		}
	}
	else
	{
		file = open(argv[1], O_RDONLY);
		int end = lseek(file, 0, SEEK_END);

		while (end--)
		{
			lseek(file, end, SEEK_SET);
			char buff[1];
			read(file, buff, 1);
			cout << buff[0];
		}

	}
	close(file);
	return 0;
}