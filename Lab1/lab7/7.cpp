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
	setlocale(LC_ALL, "");
	struct stat fileInfo;   // структура хранящая информацию об файле
	stat(argv[1], &fileInfo);
	char buff[100];
	cout << "Информация о файле " << argv[1] << ":" << endl;
	cout << "Устройство: " << fileInfo.st_dev << endl;
	cout << "inode: " << fileInfo.st_ino << endl;
	cout << "Режим доступа: " << fileInfo.st_mode << endl;
	cout << "Кол-во жестких ссылок: " << fileInfo.st_nlink << endl;
	cout << "Идентификатор пользователя-владельца: " << fileInfo.st_uid << endl;
	cout << "Идентификатор группы-владельца: " << fileInfo.st_gid << endl;
	cout << "Тип устройства: " << fileInfo.st_rdev << endl;
	cout << "Общий размер в байтах: " << fileInfo.st_size << endl;
	cout << "Размер блока ввода-вывода: " << fileInfo.st_blksize << endl;
	cout << "Количество выделенных блоков: " << fileInfo.st_blocks << endl;
	strftime(buff, 100, "%A %d %b %Y %T", localtime(&fileInfo.st_atime));
	cout << "Время последнего доступа: " << buff << endl;
	strftime(buff, 100, "%A %d %b %Y %T", localtime(&fileInfo.st_mtime));
	cout << "Время последнего доступа: " << buff << endl;
	strftime(buff, 100, "%A %d %b %Y %T", localtime(&fileInfo.st_ctime));
	cout << "Время последнего доступа: " << buff << endl;
	return 0;
}