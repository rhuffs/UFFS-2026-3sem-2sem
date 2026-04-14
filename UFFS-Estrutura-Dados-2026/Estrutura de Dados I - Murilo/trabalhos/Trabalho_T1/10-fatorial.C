#include <stdio.h>

int main()
{
    int numero, resultado = 1;
    printf("Numero para fatorar: ");
    scanf("%i", &numero);
    for (int i = numero; i > 1; i--)
    {
        resultado *= i;
    }

    printf("Resultado: %i", resultado);
    return 0;
}