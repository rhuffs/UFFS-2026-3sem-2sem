#include <stdio.h>
#include <stdlib.h>

/*
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