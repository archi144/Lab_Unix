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
using namespace std;



int main()
{
	int file = open("ALL", O_RDWR | O_CREAT, S_IRWXU);    // откр
	char str[] {"1234"};
	write(file, str, strlen(str));
	lseek(file, 100000, SEEK_CUR);   // смещение на 100 000 байт от текущей позиции
	write(file, str, strlen(str));
	close(file);
	return 0;
}