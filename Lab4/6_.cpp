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

int main(int argc, char *argv[], char *argp[])
{
    char *ChannelName = "FIFO";

    int fd_read = open(ChannelName, O_RDONLY | O_NDELAY);
    perror("");

    char buf[30];
    read(fd_read, buf, 30);
    cout << buf << endl;

    return 0;
}
