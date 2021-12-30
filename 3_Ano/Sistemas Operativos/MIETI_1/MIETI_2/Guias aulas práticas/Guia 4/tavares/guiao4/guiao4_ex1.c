#include <unistd.h>
#include <fcntl.h>
#include<stdlib.h>
#include<stdio.h>

int main(int argc; char *argv[])
{
	int fd,n;
	char buffer[1024]
	//fecha o standard input
	close(0);
	fd=open("/etc/passwd",O_RDONLY);
	assert(fd == 0);
	close(1);
	fd=open("saidas.txt",O_CREAT|O_WRONLY_|O_TRUNC,0666);
	assert(fd == 1);
	close(2);
	fd=open("erros.txt",O_CREAT|O_WRONLY_|O_TRUNC,0666);
	assert(fd == 2);
	while((n=read(0,buffer,sizeof(buffer)))>0)
		write(1,buffer,n);

	return 0;

}