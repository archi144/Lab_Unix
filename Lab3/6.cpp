#include <iostream>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <iostream>
#include <unistd.h>
#include <errno.h>
#include <proc.h>
using namespace std;


int main(int argc, char* argv[])
{
	int status = fork();
	int killStat;
	if (status)
	{
		killStat = kill(status, SIGALRM);
		wait(&status);
		cout << "WIFEXITED - " << WIFEXITED(status) << endl            // не равно нулю если процесс удачно завершился
		     << "WIFSIGNALED - "   << WIFSIGNALED(status) << endl				 // возвращает true если   дочерний   процесс   завершился   из-за неперехваченного сигнала.
		     << "WTERMSIG - "  << WTERMSIG(status) << endl;  // возвращает номер сигнала из-за которого был завершён  дочерний процесс
	}
	else
	{
		for (int i = 0; i <= 100; i++)
		{
			cout << endl;
			for (int k = 0; k <= 100; k++)
			{
				cout << i << " ";
			}
		}
	}
	cout << "Возвращенный код от дочернего процесса : " << status << endl;
	cout << "Kill завершился с кодом: " << killStat << endl;
	return 0;
}
