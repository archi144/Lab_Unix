#include <iostream>
#include <stdio.h>
#include <string>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/sendfile.h>
#include <fcntl.h>
#include <errno.h>
#include <cstring>

#define ALL 0000700
#define READ 0000400
#define WRITE 0000200
#define EXEC 0000100
#define SIZE 255
using namespace std;


int copy(char* copyFrom, char* copyTo)
{
	int src;               
    int dest;              
    struct stat stat_buf;  
    off_t offset = 0;        
    src = open(copyFrom, O_RDONLY);
    fstat(src, &stat_buf);
    dest = open(copyTo, O_WRONLY|O_CREAT, stat_buf.st_mode);
    sendfile (dest, src, &offset, stat_buf.st_size);
    close(dest);
    close(src);
	return 0;
}

int main(int argc, char* argv[])
{
	if (argv[1] != nullptr && argv[2] != nullptr)
		copy(argv[1], argv[2]);
	else
	{
		cout << "Введите имя файла из которого планируем копировать:" << endl;
		char copyFrom[10];
		cin >> copyFrom;
		cout << "Введите имя файла куда планируем копировать:" << endl;
		char copyTo[10];
		cin >> copyTo;
		copy(copyFrom, copyTo);
	}

	return 0;
}