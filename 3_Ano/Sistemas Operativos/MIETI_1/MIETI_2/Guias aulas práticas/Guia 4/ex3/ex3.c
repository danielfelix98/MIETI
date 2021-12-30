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

	close(0);
	dup(fd1);
	close(fd1);
	close(1);
	dup(fd2);
	close(fd2);
	close(2);
	dup(fd3);
	close(fd3);

	execlp("wc","wc",NULL);
}