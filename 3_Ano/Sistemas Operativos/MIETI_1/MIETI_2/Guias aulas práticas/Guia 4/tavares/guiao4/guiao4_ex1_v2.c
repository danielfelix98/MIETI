
#include <unistd.h>
#include <fcntl.h>
#include<stdlib.h>
#include<stdio.h>
int main(int argc; char *argv[])
{
	int fd,n;
	char buffer[1024]
	//fecha o standard input
	fd1= open("/etc/passwd",O_RDONLY)
	fd2 = open("saidas.txt",O_CREAT|O_WRONLY_|O_TRUNC,0666);
	fd3=open("erros.txt",O_CREAT|O_WRONLY_|O_TRUNC,0666);
	close(0);
	dup(fd1);
	close(fd1);
	close(1);
	dup(fd2);
	close(fd2);
	close(2);
	dup(fd3);
	close(fd3);
	while((n=read(0,buffer,sizeof(buffer)))>0)
		write(1,buffer,n);

	return 0;

}

