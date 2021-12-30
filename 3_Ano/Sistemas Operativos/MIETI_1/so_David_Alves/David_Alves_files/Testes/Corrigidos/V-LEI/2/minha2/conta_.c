#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <fcntl.h>


int encontra(char * palavra, char * ficheiro){
	int fd[2];
	pipe(fd);
	int pid=fork();
	char buf[1024];
	int linha=0;
	if(pid==0){
		close(fd[0]);
		dup2(fd[1],1);
		execlp("grep","grep",palavra,ficheiro,NULL);
	}

	else{
		close(fd[1]);
		int n;

		while((n=read(fd[0],buf,1024))>0){
			while(n>0){
				if(buf[n]=='\n'){
					linha++;}
				n--;
			}
		
		}
	return linha;	
	}

}




int main(int argc, char const *argv[])
{
	int total=0;
	int status;
	int pid;
	char * p;
	p=argv[1];
	for(int i=2;i<argc;i++){
		pid=fork();
		if(pid==0){
			_exit(encontra(p,argv[i]));
		}
	}
	for(int i=1;i<argc;i++){
		wait(&status);
		total=WEXITSTATUS(status);
	}

	printf("%d\n",total);


	return 0;
}