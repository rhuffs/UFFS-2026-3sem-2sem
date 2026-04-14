#include<stdio.h>
int main () {
    int n1;
    printf("Digite um numero para a soma:");
    scanf("%d", &n1);
    int valor;
    int i = 0;
    valor = i;
    while (i <= n1)
    {
        valor = valor + i;
        i = i + 1;
    }
    printf("O resultado é: %d", valor);
}