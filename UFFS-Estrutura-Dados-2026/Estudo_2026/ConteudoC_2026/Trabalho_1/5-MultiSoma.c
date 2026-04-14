#include<stdio.h>
int main () {
    int n1;
    int n2;
    int resultado;

    printf("Digite o primeiro numero inteiro:");
    scanf("%d", &n1);
    printf("Digite o segundo numero inteiro:");
    scanf("%d", &n2);
    resultado = 0;
    int i = 0;
    while (i < n2){
        resultado = resultado + n1;
        i = i + 1;
    }

    printf("O resultado é: %d", resultado);
}
