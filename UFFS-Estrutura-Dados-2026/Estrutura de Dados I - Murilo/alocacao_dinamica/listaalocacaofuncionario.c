#include <stdio.h>
#include <stdlib.h>

typedef struct {
  int id;
  char nome[50];
  double salario;
  struct funcionario *next;
}funcionario; 


funcionario *setfun(funcionario *first, int id, char name[], double dindin){
    funcionario *func = (funcionario *)malloc(sizeof(funcionario));
    func->id = id;
    func->nome = name;
    func->salario = dindin;
    func->next = NULL;
    if(first == NULL){
        first = func;
        return first;
    }
    else{
        funcionario *aux;
        for(aux = first; aux != NULL; aux = aux->next);
        aux->next = func;
        return first;
    }
}

void funcionarios(funcionario **first){

}

int main(){
    
}