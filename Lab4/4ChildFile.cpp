#include <errno.h>
#include <fcntl.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/io.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>
using namespace std;

int main(int argc, char *argv[])
{
    char buf[30];
    cout << "Выполняется дочерний файл" << endl;
    int pip = atoi(argv[1]);
    cout << " ПРИВЕТ ИЗ ДРУГОГО ФАЙЛАПолученный id pipe: " << pip << endl;

    printf("Отправьте сообщение: ");
    scanf("%s", buf);
    write(pip, &buf, strlen(buf));

    printf("\n");

    close(pip);
    // close(argv[2]);
    return 0;
}
