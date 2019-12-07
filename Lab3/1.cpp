#include <iostream>
#include <signal.h>
#include <unistd.h>
using namespace std;

void func(int i)
{
    cout << "Hello wolrd!" << endl;
    // signal(SIGINT, SIG_DFL);
}

int main()
{
    signal(SIGINT, func); // назначаем SIGINT обработчик func
    while (1)
    {
        // raise(SIGINT);
        getchar();
        fprintf(stderr, "awd");
    }
    return 0;
}