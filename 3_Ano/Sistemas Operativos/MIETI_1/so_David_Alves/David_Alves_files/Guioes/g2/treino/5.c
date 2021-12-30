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
int status,i,pid=0;
for(i=1;i<11;i++){

if(pid==0){
	printf("filho nr.%d com pid=%d, ppid=%d\n",i,getpid(),getppid());
	pid=fork();
}	
else{
	wait(&status);
	
}


}





}