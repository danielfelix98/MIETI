#include <stdio.h>

void swap (int* a, int* b) {
    int temp;
    temp = *a;
    *a   = *b;
    *b   = temp;
}

void swap1 (int** a, int** b) {
    int* temp = *a;
    *a = *b;
    *b = temp;
}

int main() {

    int a, b, *pa, *pb;

    a = 10;
    b = 20;
    printf("[antes SWAP] A=%d B=%d\n", a, b);
    swap (&a, &b);
    printf("[apos  SWAP] A=%d B=%d\n\n", a, b);

    a  = 10;
    b  = 20;
    pa = &a;
    pb = &b;
    printf("[antes SWAP1] A=%d B=%d apontador(A)=%p apontador(B)=%p\n", a, b, pa, pb);
    swap1 (&pa, &pb);
    printf("[apos  SWAP1] A=%d B=%d apontador(A)=%p apontador(B)=%p\n", a, b, pa, pb);

    return 0;
}
