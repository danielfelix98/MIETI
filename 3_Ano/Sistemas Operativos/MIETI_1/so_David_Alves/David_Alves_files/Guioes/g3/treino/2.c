#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

int main(int argc, char const *argv[])
{
	pid_t pid=fork();

	if(pid==0){
		execlp("ls","ls","-l",NULL);

	}
	else 
		printf("Esperando processo-filho...\n");


	return 0;
}