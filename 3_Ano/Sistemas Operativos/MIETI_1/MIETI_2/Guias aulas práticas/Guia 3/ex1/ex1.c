#include <unistd.h>
#include <stdio.h>

int main()
{
	execlp("ls","ls",NULL);
	printf("Erro, não devia passar aqui");
	return 0;
}
