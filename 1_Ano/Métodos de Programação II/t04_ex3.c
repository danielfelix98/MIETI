#include <stdio.h>

int funcS (int a, int b) {
    printf("a = %d\n",a);
    printf("b = %d\n\n",b);
    return 0;
}

int main(void) {

    int (*fptr)(int,int); // declarar um apontador para uma função

    fptr = funcS;         // atribuir o endereço da função funcS() ao apontador

    printf("Resultado de chamar a funcao atraves de um apontador:\n");
    fptr(2,3);            // chamar a função através de um apontador

    printf("Resultado de chamar a funcao atraves do nome:\n");
    funcS(2,3);           // chamar a função através do nome

    return 0;
}
