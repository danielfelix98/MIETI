#include <stdio.h>

struct 	empregado {
    char  pNome[100] ;
    char  uNome[100] ;
    int   idade;
    } ;

typedef struct empregado Empregado;

void printDadosEmpregado(Empregado *emp) {
    printf("--> Nome  do empregado: %s %s\n", emp->pNome, emp->uNome);
    printf("    Idade do empregado: %d\n", emp->idade);
}

int main() {

    Empregado e;

    // Confirmacao da resposta 'a segunda e 'a terceira perguntas do slide 8 da aula T03
    Empregado *pe;
    pe = &e;
    *pe.idade   = 10; // ERRO DE COMPILACAO => *pe.idade <=> *(pe.idade) nao faz sentido
    printf("Idade do empregado: %d\n",e.idade);
    (*pe).idade = 20; // CORRETO
    printf("Idade do empregado: %d\n",e.idade);
    pe->idade   = 30; // CORRETO
    printf("Idade do empregado: %d\n",e.idade);


    printf("Primeiro nome do empregado: "); // sem espaços no meio
    scanf("%s",e.pNome);

    printf("Ultimo nome do empregado: ");   // sem espaços no meio
    scanf("%s",e.uNome);

    printf("Idade do empregado: ");
    scanf("%d",&(e.idade));

    printDadosEmpregado(&e);

    return 0;
}
