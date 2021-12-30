#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <signal.h>

int main(int argc, char *argv[])
{
	int status,i;
	/*char *arg[100];
	for (i=1;i<argc;i++)
	{
		*arg[i-1] = *argv[i];
	}*/
	if (fork() == 0)
	{
		execlp(argv[1],argv[1],argv+2);
	} else {
		wait(&status);
		if (WIFEXITED(status))
		{
			int z = WEXITSTATUS(status);
			return z;
		}
		else {
			return -1;
		}
	}
}