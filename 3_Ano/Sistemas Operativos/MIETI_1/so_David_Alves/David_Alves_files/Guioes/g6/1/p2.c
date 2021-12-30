#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

int main()
{
	//mkfifo("fifo",0666);
	int fd = open("fifo",O_CREAT | O_WRONLY | O_TRUNC,0666);
	int n;
	char buffer[256];
	while ((n = read(0,buffer,sizeof(buffer))) > 0)
	{
		write(fd,buffer,n);
	}
	return 0;
}