#include <unistd.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <fcntl.h>    /* O_RDONLY, O_WRONLY, O_CREAT, O_* */
#include <sys/types.h>
#include <string.h>
//grep -v ˆ# /etc/passwd | cut -f7 -d: | uniq | wc -l

int main(){
	int err= open("erros.txt",O_WRONLY|O_CREAT);
	int out= open("output.txt",O_WRONLY|O_CREAT|O_TRUNC);
	int pid;
	int fd[2];
	pipe(fd);

	pid=fork();

	if(pid==0){
		dup2(fd[1],1);
		dup2(err,2);
		close(fd[0]);	
		close(fd[1]);

		execlp("./5","./5",NULL);
	
	}


	else{
		dup2(fd[0],0);
		dup2(out,1);

		close(fd[1]);
		close(fd[0]);
		

		for(int i=0;i<1;i++){
		

			execlp("sort","sort",NULL);
		}
	}


	return 0;
}
