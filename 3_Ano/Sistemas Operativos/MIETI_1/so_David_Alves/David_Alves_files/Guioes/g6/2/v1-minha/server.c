#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
int main()
{
	//mkfifo("fifo",0666);
	int fd = open("fifo",O_RDONLY);
	int n,n2;
	int log=open("log",O_CREAT | O_WRONLY | O_TRUNC,0666);

	char * buffer;
	while ((n = read(fd,&buffer,sizeof(buffer))) > 0)
	{
		write(1,&buffer,n);
		write(log,&buffer,n);
	}

	return 0;
}
