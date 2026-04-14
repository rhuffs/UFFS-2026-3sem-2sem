#include <stdio.h>

int lg2(int n){
    if (n < 2){
        return 0;
    } else {
        return 1 + lg2(n / 2);
    }
}

int main(){
    int numero = 16;
    int resultado = lg2(numero);
    printf("O nuemero é %d e o de divisoes é %d", numero, resultado);
    return 0;
}