#include <stdio.h>

#define MAX_SIZE 10

// EXERCICIO 2: Ordenar os elementos do array 'arr', por ordem crescente de valor,
// sem modificar este array.

int arr[MAX_SIZE] = {7, 2, 13, 6, 4, 10, 1, 17, 9, 5}; // array a ordenar

int *array_ordenado[MAX_SIZE]; // array de endereços correspondentes à ordenação de 'arr'

// Deslocar o elemento da posição anterior do array para a posição
// atual (i), até se atingir o ponto de inserção: início do array (i=0)
// ou a posição em que o elemento anterior é menor que o elemento atual.

void deslocar_elemento (unsigned int i) {
    int* valor_i;

    for(valor_i=array_ordenado[i]; (i!=0) && (*array_ordenado[i-1] > *valor_i); i--) {

        // Deslocar o elemento/apontador anterior para a posição atual
        array_ordenado[i] = array_ordenado[i-1];
    }

    // Inserir o elemento/apontador a ordenar na posição correta
    array_ordenado[i] = valor_i;
}

// Percorrer o array até encontrar um elemento fora de ordem:
// * deslocar esse elemento para a sua posição correta
// * continuar a percorrer o array.

void ordenar_por_insercao (void) {
    unsigned int  i, len;
    len = sizeof(arr)/sizeof(int); // número de elementos do array 'arr'
    for(i=1; i<len; i++)
        if(*array_ordenado[i] < *array_ordenado[i-1])
            deslocar_elemento(i);
    }

int main() {
    int i;

    // imprimir no ecrã o array antes da ordenação
    printf("Array inicial:  ");
    for(i=0;i<MAX_SIZE;++i)
        printf("%d ", arr[i]);

    // iniciar o array 'array_ordenado' com os endereços dos elementos do array 'arr'
    for(i=0;i<MAX_SIZE;++i)
        array_ordenado[i] = arr+i;

    // ordenar os endereços dos elementos de 'arr'
    ordenar_por_insercao();

    // imprimir no ecrã o resultado da ordenação
    printf("\nArray ordenado: ");
    for(i=0;i<MAX_SIZE;++i)
        printf("%d ", *array_ordenado[i]);

    printf("\n");

    return 0;
}
