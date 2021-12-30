#include <unistd.h>   //as biblios
#include <fcntl.h> 
#include <stdlib.h>
#include <string.h>   
int main(int argc, char **argv){
//char buf;//buffer
//0->stdin
//1-stdout
//2-stderr
char buf[1024];//buffer gigante //converter o numero do argumento para realmente um numero, uma vez que o  c considera os args como string
memset(buf,0,strlen(buf));
for (int i = 1; i < argc; i++){
int filed=open( argv[i], O_RDONLY );

int a=0;  
char buf3[1024];
if ( filed < 0 ) { perror( argv[i] ); continue; }//apaga conteúdo do buffer para receber o que vamos escrever de forma limpinha

while(read(filed,&buf,1024)){
a++;
sprintf(buf3,"\t%d",a);
write(1,buf3,strlen(buf3) );
write(1,"             ",1);//Enquanto ha algo p ler le em blocos de n carateres e guarda no buf
write(1,&buf,strlen(buf));//Enquanto vai lendo vai escrevendo o conteudo do buf em blocos de n caracteres no stdout
//memset(buf,0,strlen(buf));//apaga conteúdo do buffer para receber o que vamos escrever de forma limpinha
}
close(filed);
}
return 0;//so por que sim
}



  
