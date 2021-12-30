#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

int main()
{
	char buffer[1024];
	int n;
//coloca o etc/passwd no standard input
	//int fd_pass;
	close(0);
	/*fd_pass =*/ open("/etc/passwd", O_RDONLY);

//coloca o saida.txt no standard output
	//int fd_saida;
	close(1);
	/*fd_saida =*/ open("saida.txt", O_CREAT | O_WRONLY |O_TRUNC ,0644);	

//coloca o erros.txt no error
	//int fd_erros;
	close(2);
	/*fd_erros =*/ open("erros.txt", O_CREAT | O_WRONLY |O_TRUNC ,0644);

	while((n =read(0,buffer,sizeof(buffer))) > 0) 
	{
		write(1,buffer,n);
	}
	return 0;
}
