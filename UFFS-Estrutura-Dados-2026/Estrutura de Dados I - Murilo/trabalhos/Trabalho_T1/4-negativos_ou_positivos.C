#include <stdio.h>

int main()
{
    int num, neg = 0, pos = 0;

    for (int i = 1; i < 5; i++)
    {
        printf("%i° número, pode ser negativo ou positivo: ", i);
        scanf("%i", &num);

        if (num < 0)
        {
            neg++;
        }
        else
        {
            pos++;
        }
    }
    printf("\nNúmeros positivos: %i (+)\nNúmeros negativos: %i (-)", neg, pos);
    return 0;
}