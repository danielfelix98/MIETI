#include<unistd.h>
#include<fcntl.h>
#include<sys/wait.h>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"api.h"
#include<sys/stat.h>
#include<sys/types.h>
#include<signal.h>

int main()
{
	char * fifopath = malloc(12);
	char * fifopath2 = malloc(12);

	char usr[32];
	char svr[256];
	int nbytes = 0;
        fifopath = "/tmp/fifo";
	fifopath2 = "/tmp/fifo2";
	
        int fifo = open(fifopath, O_WRONLY);
        if(fifo==-1)
        {
                perror("error opening fifo...");
                return -1;
        }

	int fifo2 = open(fifopath2,O_RDONLY);
	if(fifo2 ==-1)
	{
		perror("error opening fifo2");
		return -1;
	}
	
	if(!fork())//processo que escreve p/ o pipe
	{	
		close(fifo2);
		while((nbytes=read(STDIN_FILENO, usr,32))>0)
		{	
			write(fifo,usr,nbytes);
		}
	}
	else//processo que lê do pipe
	{
		close(fifo);
		while((nbytes=read(fifo2,svr,256))>0)
		{
			write(STDOUT_FILENO,svr,nbytes);
		}
	}
	
	return 0;
}
