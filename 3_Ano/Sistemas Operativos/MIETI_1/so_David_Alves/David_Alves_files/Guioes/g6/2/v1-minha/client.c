#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

int main(int argc, char * argv[])
{
	//mkfifo("fifo",0666);
	int fd = open("fifo",O_CREAT | O_WRONLY | O_TRUNC,0666);
	//int log = open("log",O_RDONLY);
	int n;
	char * buffer;

	while ((n = read(0,&buffer,sizeof(buffer))) > 0)
	{
		write(fd,"[",1);
		write(fd,argv[1],1);
		write(fd,"]-",2);
		write(fd,&buffer,n);
	}
	return 0;
}