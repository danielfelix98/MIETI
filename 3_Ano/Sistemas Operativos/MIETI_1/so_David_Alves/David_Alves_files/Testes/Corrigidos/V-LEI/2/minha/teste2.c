
bound 10 1024 ls

void handler_sig(int sig){
	if(sig=SIGALRM) kill(pid,SIGINT);

}

int main(int argc,char * argv[]){
	int pid= fork();
	if(pid==0) {
		dup2(fd[1],1);
		close(fd[0]);
		execvp(argv[3],argv+3);

	}


	else{
		signal(SIGCHLD,handler_sig);
		signal(SIGALRM,handler_sig);
		close(fd[1]);
		size=atoi(argv[2]);

		while(n=read(fd[0],buffer,1)>0){
			count++;
			if(count==size){
				kill(pid,SIGINT);

			}
		}

		alarm(tempo);
		pause();







	}
}