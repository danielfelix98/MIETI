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
pid_t pid=fork();
if(pid==0)
printf("Sou um processo filho com pid %d e o pid do meu pai é %d \n",getpid(),getppid() );

else
printf("Sou PAI  com pid %d e o meu filho tem pid %d\n",getpid(),pid);

getchar();
	return 0;
}