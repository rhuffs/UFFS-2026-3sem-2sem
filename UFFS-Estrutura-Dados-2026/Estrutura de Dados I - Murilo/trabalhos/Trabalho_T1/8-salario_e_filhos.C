#include <stdio.h>

int main()
{
    int filhos = 0, total = 0, TotalFilhos = 0;
    float salario, MediaFilhos, MediaSalario, TotalSalario = 0;

    while (salario >= 0)
    {
        printf("Salario (menor que 0 para sair): ");
        scanf("%f", &salario);

        printf("Filhos: ");
        scanf("%i", &filhos);

        TotalFilhos += filhos;
        TotalSalario += salario;
        total++;

        printf("Salario (menor que 0 para sair): ");
        scanf("%f", &salario);
    }

    MediaFilhos = (float)TotalFilhos / total;
    MediaSalario = TotalSalario / total;
    printf("%.2f Media salarial\n%.0f Media dos filhos", MediaSalario, MediaFilhos);
    return 0;
}