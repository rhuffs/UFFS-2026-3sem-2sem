#include <stdio.h>

int main()
{
    int alcance, soma = 0;

    printf("N: ");
    scanf("%i", &alcance);

    for (int i = 1; i < alcance + 1; i++)
    {
        soma += i;
    }

    printf("Resultado: %i", soma);
    return 0;
}