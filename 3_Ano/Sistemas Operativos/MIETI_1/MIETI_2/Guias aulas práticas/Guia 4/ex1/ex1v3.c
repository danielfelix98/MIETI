#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

int main()
{
	char buffer[1024];
	int fd1,fd2,fd3,n;

	
	fd1 = open("/etc/passwd", O_RDONLY);
	fd2 = open("saida.txt", O_CREAT | O_WRONLY |O_TRUNC ,0644);
	fd3 = open("erros.txt", O_CREAT | O_WRONLY |O_TRUNC ,0644);

	dup2(fd1,0);
	close(fd1);
	dup2(fd2,1);
	close(fd2);
	dup2(fd3,2);
	close(fd3);

	while((n =read(0,buffer,sizeof(buffer))) > 0) 
	{
		write(1,buffer,n);
	}
}