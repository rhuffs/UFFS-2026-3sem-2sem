#include <stdio.h>
#include <stdlib.h>

/*
relembrando:
struct tcust{
    int id;
    char name[30];
    char email[40];
};
typedef struct tcust cust;

int main(){


    cust custmom[100];//ponteiro disfarçado
    cust *customer = (cust *) malloc(sizeof(cust) * 5);
}
*/

/*
    memory allocation = (quantidade de bytes que sejam alocado)
    endereço da memória onde os bytes foram alocados
    podemos colocar o tamanho do ponteiro/vetor ou descobrir através do syzeof
*/

typedef struct D
{
    int day, month, year;
    struct D *next; // predict no próximo valor
} Data;

void setaloc(Data **F, int d, int m, int Y, int imoufim, int a) // imoufim = 1: no início; imoufim = 2: no meio a partir do ano; imoufim = 3: no fim.
{
    Data *P = (Data *)malloc(sizeof(Data)); // cast para retornar uma função
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
        if (imoufim == 1)
        {
            P->next = *F;
            *F = P;
        }

        else if (imoufim == 2)
        {
            Data *aux;
            for (aux = *F; aux->next != NULL; aux = aux->next)
            {
                if (aux->year == a)
                    break;
            }
            P->next = aux->next;
            aux->next = P;
        }

        else if (imoufim == 3)
        {
            Data *aux;
            for (aux = *F; aux->next != NULL; aux = aux->next)
                ;
            aux->next = P;
        }
    }
}

void DeletD(Data **First, int a)
{
    if (*First == NULL)
        printf("Não há datas");
    else
    {
        Data *ant = *First;
        Data *aux;
        for (aux = *First; aux->next != NULL; aux = aux->next)
        {
            if (aux->year == a)
                break;
            ant = ant->next;
        }
        if (aux->next = NULL)
        {
            ant->next = NULL;
            free(aux);
        }
        ant->next = aux->next;
        aux->next = NULL;
        free(aux);
    }
}

void Palocall(Data **F)
{
    Data *aux;
    for (aux = *F; aux != NULL; aux = aux->next)
    {
        printf("%d/%d/%d\n", aux->day, aux->month, aux->year);
    }
}

int main()
{
    Data *first = NULL;
    int day = 4, moth = 5, year = 2006;
    setaloc(&first, day, moth, year, 1, 0);
    Palocall(&first);
    printf("\n");
    setaloc(&first, 5, 9, 2024, 1, 0);
    Palocall(&first);
    printf("\n");
    setaloc(&first, 3, 2, 2001, 2, 2024);
    Palocall(&first);
    DeletD(&first, 2001);
    printf("\n");
    Palocall(&first);
}

/*RECEITINHA DE BOLO
1) alocar o espaço;
2)colocar os valores no espaço e nullificar os ponteiros
3)guardar

*/
/*
    dt = (Data *)malloc(sizeof(Data));
    dt->day = 5;// não pode ser dt.day
    dt->month = 8;
    dt->year = 2021;
    dt->next = NULL;
    *first = *dt;
    dt = (Data *)malloc(sizeof(Data));aqui, perderemos a data anterior e criaremos uma nova: como resolve
    dt->day = 11;
    dt->month = 9;
    dt->year = 2021;
    dt->next = NULL;
    first->next = dt;
    for(aux = first; aux != NULL; aux = aux->next){
        printf("%d/%d/%d\n", aux->day, aux->month, aux->year);
    }
*/