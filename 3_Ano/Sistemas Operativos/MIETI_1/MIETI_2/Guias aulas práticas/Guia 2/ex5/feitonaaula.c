#include <unistd.h>
#include <stdlib.h>

int main()
{
	int i,status;
	for (i=0;i<10;i++)
	{
		if (fork() == 0)
		{
			printf("Eu sou %d meu pai %d\n",getpid(),getppid());
		} else {
			wait(&status);
			printf("Morri %d\n",getpid());
			_exit(0);
		}
	}	
	printf("final %d\n\n",getpid());
	return 0;
}
