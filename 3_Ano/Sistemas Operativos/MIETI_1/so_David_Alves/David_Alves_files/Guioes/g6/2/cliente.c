#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char* argv[]){
	int fd = open("fifo",O_RDONLY);
	int n = strlen(argv[1]);
	char buffer[n+1];
	memcpy(buffer,argv[1],n);
	buffer[n] = '\n';

	write(fd,buffer,n+1);
	return 0;
}
