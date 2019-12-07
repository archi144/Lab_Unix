#include <iostream>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <iostream>
#include <unistd.h>
#include <proc.h>
using namespace std;


int main(int argc, char* argv[])
{
	int status = fork();
	if (status)
	{

		wait(&status);
	}
	else
	{
		for (int i = 0; i <= 100; i++)
		{
			cout << i << " ";
			for (int k = 0; k <= 100; k++)
			{
				
			}
		}
	}
	cout << "status : " << status << endl;
	return 0;
}
