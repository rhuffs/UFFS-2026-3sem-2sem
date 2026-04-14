#include <stdio.h>

int main()
{
    float salario;
    int horas, ValordHoras;

    printf("Quantas horas trabalhadas?  ");
    scanf("%i", &horas);
    printf("Valor por Horas trabalhadas: ");
    scanf("%i", &ValordHoras);

    if (horas > 200)
    {
        salario = horas * ValordHoras;
        int acrescimo = salario * 0.05;
        salario += acrescimo;
    }
    else
    {
        salario = horas * ValordHoras;
    }

    printf("\nResultado do seu salário: %.2f", salario);
    return 0;
}