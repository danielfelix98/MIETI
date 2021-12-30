#include <sys/types.h>
#include <sys/stat.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/wait.h>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>


int main() {
	int fd;	
	fd=mkfifo("/home/ubuntu/Desktop/so_/g6/1/fifo", 0666);
	if(fd==-1) {
		perror("erro criaÃ§ao fifo...");
	}
	
	else{
		printf("fifo criado\n");
	}
	return 0;
}
