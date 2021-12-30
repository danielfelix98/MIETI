/*
vai dar asneira pois os argumentos recebidos só têm x bytes reservados, o tamanho necessário para os argumentos anteriores, e ao escrever por cima mais do que x bytes, vai escrever em cima de outros argumentos e mais coisas que estão à frente que não vemos, como o ambiente
*/
#include <stdio.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char *argv[])
{
	strcpy(argv[1],"12345678901234567890");
	execv("./ex3",argv);
	printf("Erro, não devia passar aqui.\n");
}
