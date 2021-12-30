#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <signal.h>

ssize_t readln(int fildes,void *buf,ssize_t nbyte)
{
	int n,i=0;
	while ((n = read(fildes,(buf+i),1)) > 0)
	{
		if (*(char*)(buf+i) == '\n')
		{
			i++;
			break;
		}
		i++;
	}
	return i;
}

int main(int argc, char *argv[])
{
	int n,i=1;
	char buffer[256];
	if (argc > 1)
	{
		close(0);
		int fd = open(argv[1],O_RDONLY);
		if (fd == -1)
		{
			perror("Erro a abrir ficheiro");
		}
	}
	while ((n = readln(0,buffer,256)) > 0)
	{
		char string[10];
		sprintf(string,"%d ",i);
		i++;
		write(1,string,strlen(string));
		write(1,buffer,n);
	}
	return 0;
}