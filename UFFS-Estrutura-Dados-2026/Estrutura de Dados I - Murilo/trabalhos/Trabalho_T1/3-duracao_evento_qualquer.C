#include <stdio.h>

int main()
{
    int inicio, fim, resultado;

    printf("Inicio: ");
    scanf("%i", &inicio);
    printf("Fim: ");
    scanf("%i", &fim);

    if (inicio > fim)
    {
        resultado = (24 - inicio) + fim;
    }

    else if (inicio < fim)
    {
        resultado = inicio - fim;
    }

    else
    {
        resultado = 24;
    }

    printf("%i Horas de duração", resultado);
    return 0;
}