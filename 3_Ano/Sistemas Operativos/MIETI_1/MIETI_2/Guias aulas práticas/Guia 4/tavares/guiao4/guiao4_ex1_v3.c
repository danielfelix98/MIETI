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
	dup2(fd1,0);
	close(fd1);
	dup2(fd2,1);
	close(fd2);
	dup2(fd3,2);
	close(fd3);
	while((n=read(0,buffer,sizeof(buffer)))>0)
		write(1,buffer,n);

	return 0;

}