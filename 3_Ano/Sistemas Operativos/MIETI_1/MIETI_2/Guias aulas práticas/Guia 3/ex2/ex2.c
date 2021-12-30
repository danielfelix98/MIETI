#include <unistd.h>
#include <stdio.h>

int main()
{
	if (fork() == 0)
	{
		execlp("ls","ls",NULL);
		printf("Erro, não devia passar aqui.\n");
	}
	return 0;
}
