#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <sys/wait.h>
int main(int argc, char *argv[])
{


printf("Sou um processo com pid %d e o pid do meu pai é %d \n",getpid(),getppid() );


	return 0;
}