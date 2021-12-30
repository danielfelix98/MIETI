
#include <unistd.h>
#define READ 0
#define WRITE 1
#define N 32

int main(int argc, char** argv){

	int fd[2];
	pipe(fd);
	int pid=fork();
	char buf;

	if(pid==0){
		//PROCESSO FILHO
		close(fd[WRITE]);
		dup2(fd[READ],0);
		execlp("wc","wc",NULL);

	}
	else{
		//PROCESSO PAI
		close(fd[READ]);
		dup2(fd[WRITE],1);
		close(fd[WRITE]);
		while(read(0,&buf,1)){
			write(1,&buf,1);
		}
		

	}

	return 1;
}