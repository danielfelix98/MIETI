#include <unistd.h>   //as biblios
#include <fcntl.h>    
int main(int argc, char **argv){
char buf;//buffer
while(read(0,&buf,1)){//Enquanto ha algo p ler le um a um e guarda no buf
write(1,&buf,1);//Enquanto vai lendo vai escrevendo o conteudo do buf um a um no stdout
}

return 0;//so por que sim
}
//Uma vez que não se está a ler o conteúdo de um ficheiro, mas sim a imprimir o que se escreve, fazia mais sentido chamar-se myEcho, mas pronto...Viva SO!
