#include <stdio.h>

int main() {

    int arr[8];
    int i, j, *pa3;

    int  *pa = arr;

    char *pc = (char *)pa;

    // Que valor de i satisfaz: (int ∗)(pc+i) == (pa+3) ?

    printf("Endereco de memoria de arr[0]: %p\n\n",arr);

    for (j=0;j<8;++j) {
        printf("Endereco pa+%d: %p\n",j,pa+j);
        if(j==3) {
            pa3 = pa+j;
        }
    }

    printf("\n");

    for (i=0;i<32;++i) {
        printf("Endereco pc+%d: %p\n",i,pc+i);
        if ((int *)(pc+i)==pa3) {
            printf("\n==> O valor de i que satisfaz: (pc+i==pa+3) e' %d\n",i);
            break;
        }
    }

    return 0;
}
