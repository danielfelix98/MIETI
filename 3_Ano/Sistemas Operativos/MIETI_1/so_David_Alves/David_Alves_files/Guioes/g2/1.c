#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include <sys/wait.h>
int main()
{
	printf("Sou o filho, com PID %d, e o meu pai é %d\n",getpid(),getppid());
	return 0;
	
}
/*ubuntu@ubuntu:~/Desktop/so_/g2$ ./1
Sou o filho, com PID 33041, e o meu pai é 33004
ubuntu@ubuntu:~/Desktop/so_/g2$ ps
   PID TTY          TIME CMD
 33004 pts/1    00:00:00 bash
 33042 pts/1    00:00:00 ps*/
