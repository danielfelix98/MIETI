
#include <unistd.h>
#include <unistd.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <fcntl.h>    /* O_RDONLY, O_WRONLY, O_CREAT, O_* */
#include <sys/types.h>
#include <string.h>
#define READ 0
#define WRITE 1
#define N 32

int main(int argc, char * argv){

	int pd[2];
	pipe(pd);
	int pid=fork();
	char buf[N];

	if(pid==0){
		//PROCESSO FILHO
		close(pd[WRITE]);
		read(pd[READ],&buf,N);
		close(pd[READ]);
		write(1,&buf,N);

	}
	else{
		//PROCESSO PAI
		close(pd[READ]);
		write(pd[WRITE],"abc\n",N);
		close(pd[WRITE]);
	}

	return 1;
}