#include <stdio.h>

// VERIFICAR A INFLUÊNCIA DO ALINHAMENTO DAS VARIÁVEIS

struct ex1 {
    char c1;
    char c2;
};

struct ex1_aligned {
    char  c1 __attribute__((aligned(4)));
    char  c2 __attribute__((aligned(4)));
};

int main(void){
    struct ex1         e;
    struct ex1_aligned ea;

    printf("Tamanho da estrutura sem alinhamento= %lu\n", sizeof(e));
    printf("\t Endereço do primeiro campo: %p\n",&e.c1);
    printf("\t Endereço do segundo  campo: %p\n",&e.c2);

    printf("Tamanho da estrutura com alinhamento= %lu\n", sizeof(ea));
    printf("\t Endereço do primeiro campo: %p\n",&ea.c1);
    printf("\t Endereço do segundo  campo: %p\n",&ea.c2);

    return 0;
}

