#include<unistd.h>
#include<fcntl.h> /* por causa das flags */
#include<stdio.h>

int main(int argc, char *argv[])
{
	if (argc != 2)
	{
		printf("Número errado de parâmetros");
	}
	else {
		int fd_output;
		//O_TRUNC limpa o ficheiro e começa a escrever do inicio
		fd_output = open(argv[1], O_CREAT | O_WRONLY |O_TRUNC ,0644); /*0644 é uma permissao dada pelo user, é arbitraria, mas o standard é o valor 0666(base octal) */
		if (fd_output == -1)
		{
			perror(argv[1]);
			return 1;
		}
		int i;
		char c = 'a';
		for (i=0;i<10*1024*1024;i++)
		{
			write(fd_output, &c,sizeof(c));
		}
		close(fd_output);
	}
	return 0;
}
