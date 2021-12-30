#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
int main(){
	mkfifo("fifo",0666);
	int fd = open("fifo",O_WRONLY);
	int f = open("log",O_CREAT | O_WRONLY);
	int n;
    char buffer[256];
	
	while(n=(read(fd,buffer,sizeof(buffer)))>0){
		write(f,buffer,n);
        write(1,buffer,n);
	}
	return 0;
}
