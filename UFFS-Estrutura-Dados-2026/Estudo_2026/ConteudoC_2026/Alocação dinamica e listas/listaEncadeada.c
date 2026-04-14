#include <stdio.h>
#include <stdlib.h>

/*typedef struct tcust
{
    int id;
    char nome[30];
    char email[40];
}cust;


int main(){
    /*cust *customer;
    customer = (cust *)malloc(sizeof(cust)*100);
    customer[0];*/

    //LISTA ENCADEADA

typedef struct data{
    int dia, mes, ano;
    struct data *next;
} data;
 

int main (){
    data *dt, *first = NULL, *aux;
    dt = (data *)malloc(sizeof(data));
    dt->dia = 5;
    dt->mes = 8;
    dt->ano = 2000;
    dt->next = NULL;
    *first = *dt;
    
    dt = (data *)malloc(sizeof(data));
    dt->dia = 11;
    dt->mes = 5;
    dt->ano = 2010;
    dt->next = NULL;
    first->next = dt;

    dt = (data *)malloc(sizeof(data));
    dt->dia = 12;
    dt->mes = 5;
    dt->ano = 2007;
    dt->next = NULL;
    first->next = dt;
    

    for(aux = first; aux!=NULL; aux = aux->next){
        printf("%d/%d/%d\n",aux->dia,aux->mes,aux->ano);
    }
    /*1) alocar o espaço
      2)Colocar os valores no espaço e nullificar os ponteiros
      3)encandear*/


    


}