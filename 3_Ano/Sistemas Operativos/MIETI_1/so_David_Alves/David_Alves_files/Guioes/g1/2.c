//https://www.linuxquestions.org/questions/programming-9/how-to-create-a-file-of-pre-defined-size-in-c-789667/
//http://codewiki.wikidot.com/c:system-calls:lseek
#include <unistd.h>   //as biblios
#include <fcntl.h>    
#include <stdio.h> 
#define FILESIZE 10000000//tamanho 10⁶ bytes
int main(int argc, char **argv){

//char a = a;
int ficheiro;
int resultado;

if(argc<2){//Se não houver argumento no prog
printf("Tens que dar um nome ao programa!!\n");
return -1;}
else{
//permission to:  owner      group      other     
//                /¯¯¯\      /¯¯¯\      /¯¯¯\

//octal:            6          6          6
//binary:         1 1 0      1 1 0      1 1 0
//what to permit: r w x      r w x      r w x

ficheiro= open(argv[1],O_WRONLY|O_CREAT|O_TRUNC,0666);//cria ou abre o prog com o nome dado no arg
if(ficheiro==-1){
printf("Nada de nada");
return -1;
}

resultado=lseek(ficheiro,FILESIZE-1,SEEK_SET);
if(resultado==-1){
close(ficheiro);
perror("ERRO!!");
return 1;
}

//for(int i=0;i < 10000000;i++){
resultado=write(ficheiro,"",1);}
if(resultado<0){
close(ficheiro);
perror("ERRO!!");
return 1;
}
close(ficheiro);
return 0;
}
