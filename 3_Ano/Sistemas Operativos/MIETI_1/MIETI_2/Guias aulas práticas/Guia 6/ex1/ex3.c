#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

int main()
{
	//mkfifo("fifo",0666);
	int fd = open("fifo",O_RDONLY);
	int n;
	char buffer[256];
	while ((n = read(fd,buffer,sizeof(buffer))) > 0)
	{
		write(1,buffer,n);
	}
	return 0;
}