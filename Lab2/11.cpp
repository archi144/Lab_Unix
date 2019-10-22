#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <errno.h>
#include <cstring>
#include <unistd.h>
#include <stddef.h>
using namespace std;


int main(int argc, char* argv[])
{
	extern char **environ;
	fork();
	execvp(argv[1], (argv + 2));
	system(argv[1]);
	return 0;
}


