#include <stdio.h>

int main()
{
    int multiplicador, multiplicando, somador = 0;

    printf("Multiplicador: ");
    scanf("%i", &multiplicador);
    printf("Multiplicado: ");
    scanf("%i", &multiplicando);

    for (int i = 0; i < multiplicando; i++)
    {
        somador += multiplicador;
    }
    printf("\nResultado: %i", somador);
    return 0;
}
