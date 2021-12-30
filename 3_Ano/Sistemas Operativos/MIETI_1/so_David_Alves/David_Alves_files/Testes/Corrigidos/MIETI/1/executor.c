#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <fcntl.h>

/*Este programa serve para executar varios programas dados como args, sendo que o output de todos deve ser escrito 
num ficheiro pid.out.Enquanto esta a ser executado cada programa, deve ser apresentado no stdout [N- de processo]:E
Quando acabar a execucao deve apresentar [nº de processo]:S, e se nao conseguir executar, deve ser executado outra vez e 
aparecer [nº de processo]:R
*/
int main(int argc, char const *argv[])
{
	int fd= open("pid.out",O_CREAT|O_TRUNC|O_WRONLY,0666);
	int pids[argc];
	int i=0;
	int status;
	int pid;
	for(int i=1;i<argc;i++){
		pid=fork();
		
		if(pid==0){
			dup2(fd,1);
			close(fd);
			execlp(argv[i],argv[i],NULL);
			perror("erro");
			exit(-1);
		}
		pids[i]=pid;
		printf("%d:E\n",pid);
	}


	while(i<argc-1){
		int pid_=wait(&status);

		if(WEXITSTATUS(status)==0){
			printf("%d:S\n",pid_);
			i++;			
		}

		else{
			for(int i=0;i<argc-1;i++){
				if(pid_==pids[i]){
					execlp(argv[i],argv[i],NULL);
				}
			}
			printf("%d:R\n",pid_);
		}

	}

	
}