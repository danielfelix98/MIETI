#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
	int n,status;
	for (n=1;n<argc;n++)
	{
		if (!fork())
		{
			execlp(argv[n],argv[n],NULL);
			printf("Erro, não devia passar aqui.\n");
			_exit(-1);
			
		}
	}

	for (n=1;n<argc;n++)
	{
		wait(&status);
	}

	printf("Sou o programa pai e acabei\n");
	return 0;
}
