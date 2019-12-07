#include <cstring>
#include <fcntl.h>
#include <iostream>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
using namespace std;
int main(int argc, char *argv[])
{
    // обнуляем маску чтоб не заблочить права доступа
    // ибо права доступа становятся равны (mode & ~umask).
    char *ChannelName = "FIFO";
    umask(0);
    mkfifo(ChannelName, S_IFIFO | 0660); // константа IFIFO означает, что файл типа именованного канала
    perror("");
    // Без флага O_NDELAY - на чтение блокируется, пока какой-либо процесс не откроет на запись;
    // на запись блокируется, пока какой-либо процесс не откроет на чтение

    // При O_NDELAY без задержки
    int fd_read = open(ChannelName, O_RDONLY | O_NDELAY);
    perror("");

    // Если O_NDELAY и нет процесса на чтение - ошибка
    int fd_write = open(ChannelName, O_WRONLY | O_NDELAY);
    perror("");
    char buf[]{"Hello world!"};
    write(fd_write, buf, strlen(buf));
    pause();
}