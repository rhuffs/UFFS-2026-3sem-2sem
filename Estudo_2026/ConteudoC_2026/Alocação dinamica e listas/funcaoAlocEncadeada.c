#include <stdio.h>
#include <stdlib.h>


typedef struct D
{
    int day, month, year;
    struct D *next;
} Data;

void setaloc(Data **F, int d, int m, int Y)
{

    Data *P = (Data *)malloc(sizeof(Data));
    P->day = d;
    P->month = m;
    P->year = Y;
    P->next = NULL;
    if (*F == NULL)
    {
        *F = P;
    }
    else
    {
        Data *aux;
        for (aux = *F; aux->next != NULL; aux = aux->next){}
        aux->next = P;
    }
}

void Palocall(Data **F){
    Data *aux;
    for (aux = *F; aux != NULL; aux = aux->next)
    {
        printf("%d/%d/%d\n", aux->day, aux->month, aux->year);
    }
}

int main()
{
    Data *first = NULL, *aux;
    int day = 4, moth = 5, year = 2006;
    setaloc(&first, day, moth, year);
    Palocall(&first);
    setaloc(&first, 5,9,2024);
    Palocall(&first);
    
}