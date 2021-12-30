//Uma vez que não se está a ler o conteúdo de um ficheiro, mas sim a imprimir o que se escreve, fazia mais sentido chamar-se myEcho, mas pronto...Viva SO!
#include <unistd.h>   //as biblios
#include <fcntl.h> 
#include <stdlib.h>
#include <string.h>   
int main(int argc, char **argv){
//char buf;//buffer
//0->stdin
//1-stdout
//2-stderr
char buf[1024];//buffer gigante
int n=strtol(argv[1],NULL,10);//converter o numero do argumento para realmente um numero, uma vez que o  c considera os args como string
memset(buf,0,strlen(buf));//apaga conteúdo do buffer para receber o que vamos escrever de forma limpinha
while(read(0,&buf,n)){//Enquanto ha algo p ler le em blocos de n carateres e guarda no buf
write(1,&buf,strlen(buf));//Enquanto vai lendo vai escrevendo o conteudo do buf em blocos de n caracteres no stdout
memset(buf,0,strlen(buf));//apaga conteúdo do buffer para receber o que vamos escrever de forma limpinha
}

return 0;//so por que sim
}
//comparação dos tempos
/*[31]+  Stopped                 ./3 1

real	0m7.710s
user	0m0.001s
sys	0m0.000s

[32]+  Stopped                 ./3 1024

real	0m5.205s
user	0m0.001s
sys	0m0.000s






  
