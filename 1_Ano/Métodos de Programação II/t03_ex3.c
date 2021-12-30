#include <stdio.h>

struct 	empregado {
    char  pNome[100];
    char  uNome[100];
    int   idade;
    } ;

typedef struct empregado Empregado;

void printDadosEmpregado(Empregado *emp) {
    printf("--> Nome  do empregado: %s %s\n", emp->pNome, emp->uNome);
    printf("    Idade do empregado: %d\n", emp->idade);
}

// Formato do ficheiro com empregados:
//   PrimeiroNome_1 UltimoNome_1 Idade_1
//   ...
//   PrimeiroNome_N UltimoNome_N Idade_N
//
void LerEmpregados(FILE *fp) {
    Empregado e;
    int       n;

    do {
        n=fscanf(fp,"%s %s %d", e.pNome, e.uNome, &(e.idade));
        if (n == 3)
            printDadosEmpregado(&e);
        else if (n==EOF)
           printf("*** Fim de ficheiro!\n");
        else // (n<3) && (n != EOF)
           printf("*** Linha incompleta!\n");
    } while ( n != EOF );
}

// argv[1] = nome do ficheiro com os dados dos empregados

int main(int argc, char *argv[]) {

    FILE *fp;

    if (argc < 2) {
        printf("Passe o nome do ficheiro a abrir como argumento!\n");
        return 1;
   }
    else if ((fp = fopen(argv[1], "r")) == NULL) {
        printf("Nao e' possivel abrir o ficheiro %s\n", argv[1]);
        return 1;
    }
    else {
        LerEmpregados(fp);
        fclose(fp);
        return 0;
    }

}
