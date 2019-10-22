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
	struct stat fileInfo[argc];
	int greatest;
	for (int i = 0; i < argc; i++)   // заполняем массив структур статистикой о файлах, передаваемыех в параметрах
	{
		stat(argv[i], &fileInfo[i]);
	}
	for (int i = 0; i < argc - 1 ; i++) // сравнием размеры полученных файлов
	{
		int firstVal = fileInfo[i].st_size;
		int secondVal = fileInfo[i + 1].st_size;
		firstVal > secondVal ? greatest = firstVal : greatest = secondVal;
	}
	cout << "Наибольший файл размером: " << greatest << endl;
	return 0;
}