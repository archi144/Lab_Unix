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
	int file = open(name,O_CREAT | O_TRUNC | O_RDWR,rights);
	cout << "Дескриптор созданного файла " << name << ": " << file << endl;
	char str[] {"1.One\n2.Two\n3.Three\n4.Four\n5.Five"};
	cout << "Записываем в файл " << name << "..." << endl;
	int lengthSTR = strlen(str);    // длина записанной строки
	write(file, str, lengthSTR);  // сохраняем длину строки, которую записали в файл
	close(file);
	cout << "Закрыли файл " << name << "..." << endl;
	cout << "Открываем файл " << name << " на чтение..." << endl;
	file = open(name, O_RDONLY);         // открываем файл на чтение
	cout << "Дескриптор открытого файла " << name << ": " << file << endl;
	char buffer[lengthSTR - 1];  // все проблемы исходят отсюда
	read(file, buffer, lengthSTR);
	cout << "Содержимое файла " << name << ": " << endl;
	cout << buffer << endl;
	close(file);
	cout << "Закрыли файл " << name << "..." << endl;
	cout << "Открываем файл " << name << " на чтение и запись" << endl;
	cout << "Дескриптор вновь открытого файла " << name << ": " << open(name, O_RDWR) << endl; // O_RDWR - чтение и запись
	cout << strerror(errno) << endl;
	close(file);
	return 0;
}


