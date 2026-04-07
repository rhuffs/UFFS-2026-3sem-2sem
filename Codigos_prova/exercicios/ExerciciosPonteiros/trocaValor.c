#include <stdio.h>

void trocaValor(int *p, int *q){
    int aux = *p;  //aux nao precisa ser um ponteiro, pois estamos guardando valor *p significa 'endereço apontado por p'
    *p = *q;       // o valor apontado por p recebe o valor apontado por q
    *q = aux;  //o valor apontado por q recebe o valor int aux, que era do inteiro apontado por p

}

int main(){
    int a = 10;
    int b = 20;
    trocaValor( &a, &b);
    printf("a : %d \n  b : %d", a, b);
} 