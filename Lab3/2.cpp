#include <iostream>
#include <signal.h>
#include <unistd.h>
using namespace std;

void func(int i)
{
    cout << "Hello wolrd!" << endl;
}

int main()
{
    struct sigaction *baseStruct; // эта структура нужна для инициализации константной структуры
    baseStruct->sa_handler = func;
    baseStruct->sa_flags = SA_RESTART; // SA_ONESHOT;
    struct sigaction const *structForSigact(baseStruct);
    sigaction(SIGINT, structForSigact, 0);
    while (1)
    {
        // raise(SIGINT);
        getchar();
        fprintf(stderr, "awd");
    }
    cout << "Efef";
    return 0;
}