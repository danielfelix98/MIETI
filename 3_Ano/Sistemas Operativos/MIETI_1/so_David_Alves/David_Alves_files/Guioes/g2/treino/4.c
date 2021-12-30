#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <sys/types.h> 
#include <unistd.h>
int main(int argc, char const *argv[])
{
int status,pid=1,i;
for (i = 1; i <11; i++)
{
	if(pid!=0){
	pid=fork();}
	else break;

}

if(pid!=0){
	for(i=1;i<11;i++){
	wait(&status);
	printf("processo-filho nr.%d, com ppid %d terminou\n",WEXITSTATUS(status),pid);
	}
}
else{
printf("Sou o filho nr.%d, com pid %d, e o meu pai tem pid=%d\n",i,getpid(),getppid());
_exit(i);



}



return 0;
}