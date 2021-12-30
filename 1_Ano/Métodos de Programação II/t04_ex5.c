#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 10

// compare() para ordenar por ordem crescente
int crescente(const void* pa, const void* pb) {
return(*(int *)pa - *(int *)pb);
}

// compare() para ordenar por ordem decrescente
int decrescente(const void* pa, const void* pb) {
return(*(int *)pb - *(int *)pa);
}

int main() {

    int arr[MAX_SIZE]={10,4,9,6,8,1,2,7,5,3};
    int i;

    printf("\nARRAY ORIGINAL                       -> ");
    for(i=0;i<MAX_SIZE;++i)
        printf("%d ",arr[i]);

    // ordenar valores por ordem crescente
    qsort(arr, sizeof(arr)/sizeof(int), sizeof(int), crescente);

    printf("\nARRAY ORDENADO POR ORDEM CRESCENTE   -> ");
    for(i=0;i<MAX_SIZE;++i)
        printf("%d ",arr[i]);

    // ordenar valores por ordem decrescente
    qsort(arr, sizeof(arr)/sizeof(int), sizeof(int), decrescente);

    printf("\nARRAY ORDENADO POR ORDEM DECRESCENTE -> ");
    for(i=0;i<MAX_SIZE;++i)
        printf("%d ",arr[i]);

    return 0;
}
