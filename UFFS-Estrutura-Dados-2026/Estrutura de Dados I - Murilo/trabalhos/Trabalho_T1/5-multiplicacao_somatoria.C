#include <stdio.h>

int main()
{
    int num1, num2, somador = 0;

    printf("Multiplicador: ");
    scanf("%i", &num1);
    printf("Multiplicado: ");
    scanf("%i", &num2);

    for (int i = 0; i < num2; i++)
    {
        somador += num1;
    }
    printf("Resultado: %i", somador);
    return 0;
}