#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <sys/types.h> 
#include <unistd.h>


int main(){

	pid_t pid=fork();//tambem pode ser do tipp int
	if(pid==-1){
		printf("erro");
		return -1;}
		
	if(pid==0){
		//ESTAMOS NO FILHO
		printf("::Filho:: PID: %d ParentPID: %d\n",getpid(),getppid());
	}
	else{
		//ESTAMOS NO PAI
		printf("::Pai:: PID: %d ParentPID: %d CHILD_PID: %d\n",getpid(),getppid(),pid);
		
	}
	getchar();//so para que veja melhor
	return 0;

}