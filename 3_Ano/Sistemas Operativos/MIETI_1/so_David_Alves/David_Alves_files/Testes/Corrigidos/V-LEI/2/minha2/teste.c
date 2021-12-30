conta ola 3.c


int encontra(char * palavra, char * fich){
	int pid=fork();
	if(pid==0){
		dup2(fd[1],1);
		close(fd[0]);
		execlp("grep","grep",palavra,fich);

	}
	else()




}



int main(int argc, char const *argv[])
{
	
	return 0;
}