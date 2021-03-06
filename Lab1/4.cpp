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
#define SIZE 20
using namespace std;



int main()
{
	char name[20];  // имя файла
	mode_t rights;  // права
	int change;
	cout << "Введите имя файла: ";
	cin >> name;
	cout << "\nВыберите права доступа файла: " << endl;
	cout << "1. Право на чтение \t 2. Право на запись "
	     << "\n3. Право на выполнение \t 4. Всё вместе." << endl;
	scanf("%d", &change);
	switch (change)
	{
	case 1:
		rights = READ;
		break;
	case 2:
		rights = WRITE;
		break;
	case 3:
		rights = EXEC;
		break;
	case 4:
		rights = ALL;
		break;
	default:
		cout << "ERROR" << endl;
	}
	int file = creat(name, rights);
	char str1[] {"11"};
	int lengthSTR = strlen(str1);
	int offset;
	cout << "Задайте смещение записи в файл относительно начала: ";
	cin >> offset;
	cout << endl;
	write(file, "0000000000", 10);
	write(file, "0000000000", 10);
	write(file, "0000000000", 10);
	write(file, "0000000000", 10);
	write(file, "0000000000", 10);
	lseek(file, offset, SEEK_SET);
	cout << "Записываем в  " << name << " со смещением " << offset << " относительно начала файла..." << endl;
	write(file, str1, lengthSTR);
	cout << "\nЗадайте смещение записи в файл относительно текущей позиции: ";
	cin >> offset;
	cout << endl;
	lseek(file, offset, SEEK_CUR);
	char str2[] {"2222"};
	lengthSTR = strlen(str2);
	cout << "Записываем в  " << name << " со смещением " << offset << " относительно текущей позиции в файле..." << endl;
	write(file, str2, lengthSTR);

	cout << "\nЗадайте смещение записи  со знаком минус  в файл относительно конца файла: ";
	cin >> offset;
	cout << endl;
	lseek(file, offset, SEEK_END);
	char str3[] {"333333"};
	lengthSTR = strlen(str3);
	cout << "Записываем в  " << name << " со смещением " << offset << " относительно конца файла..." << endl;
	write(file, str3, lengthSTR);
	//fwrite(str3, sizeof(char), lengthSTR, file);
	close(file);
	return 0;
}