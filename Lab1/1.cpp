#include <iostream>
#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <cstring>
#include <unistd.h>
using namespace std;


int main()
{
	int file = open("./1.cpp",O_RDONLY);                    // открываем файл с правами только на чтение
	cout<<"errno - " <<errno<<endl;                   // возвращает код последней операции
	cout<<"sys_errlist[] - "<<sys_errlist[errno]<<endl;           // массив возвращаемых значений
	perror(sys_errlist[errno]);     //  вместо номера ошибки выводит описание ошибки
	close(file);
	return 0;
}