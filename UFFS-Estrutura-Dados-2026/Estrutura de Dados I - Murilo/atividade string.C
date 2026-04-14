#include <stdio.h>
#include <string.h>

void saifora(char *V)
{
    int tam = strlen(V);
    for (int i = tam; i >= 0; i--)
    {
        printf("%c", V[i]);
    }
    printf("\n");
}

void vogal(char *st)
{
    int adicionar = 0;
    int tam = strlen(st);
    char vogal[5] = {'a', 'e', 'i', 'o', 'u'};
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < tam; j++)
        {
            if (vogal[i] == st[j])
            {
                adicionar++;
            }
        }
    }
    printf("ha, %i vogais na sua palavra", adicionar);
}

int main()
{
    char st[5];
    strcpy(st, "hoje");
    saifora(st);
    char string[100];
    printf("apenas escreva...");
    scanf("%s", string); // esqueci de colocarkk, mas como isso é um vetor, ou seja, um ponteiro disfarçado
                         // não precisa colocar um & (um E comercial)
    saifora(string);
    vogal(string);
}