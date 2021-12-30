#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#define LS "/bin/ls"

int main(){
	char str[100];
	printf("O comando ls -l vai executado de que forma?\n");
	printf("Escreve a opção:execl,execlp,execv,execvp\n");
	scanf("%s",str);
	printf("Escolheste o %s\n",str);
	if(strcmp("execl",str)==0){

	execl("/bin/ls","ls","-l",NULL);//-->so isto
	}	
	
	if(strcmp("execlp",str)==0){
	execlp("ls","ls","-l",NULL);//-->so isto

	if(strcmp("execv",str)==0){
	char * args[]={LS,"-l",NULL};//-->usar juntamente com o execv
	execv(LS,args);}
	
	if(strcmp("execvp",str)==0){
	char * argsvp[]={"ls","-l",NULL};//-->usar com execvp
	execvp("ls",argsvp);}
	return 0;
}}