#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "biblio.h"

//Raízes
NoBooks *raizeslivros = NULL;
NoUser *raizesusuarios = NULL;
//alocar o Livro
NoBooks *NoPlivro(Books *L){
    NoBooks *newL = (NoBooks *)malloc(sizeof(NoBooks));
    newL->Livro = L;
    newL->dir = NULL;
    newL->esq = NULL;
    return newL;
}

//inserir novo livro
NoBooks *InsertNewBook(NoBooks *raizL, Books *Livro){
    NoBooks *NewL = NoPlivro(Livro);
    if(raizL == NULL) return NewL;
    else{
        NoBooks *aux = raizL;
        NoBooks *pai = NULL;
        while(aux != NULL){
            pai = aux;
            if(aux->Livro->id > Livro->id) aux = aux->esq;
            else if(aux->Livro->id < Livro->id) aux = aux->dir;
            else{
                printf("!!ERROR!!\n>ID(%d) do livro já existe", Livro->id);
                free(Livro);
                free(NewL);
                return raizL;
            }
        }
        if(pai->Livro->id > Livro->id) pai->esq = Livro;
        else pai->dir = Livro;
        return raizL;
    }
}

Books findBook(NoBooks *Livro,  int id){
    NoBooks *aux = Livro;
    while(aux != NULL){
        if(id == aux->Livro->id) return aux->Livro;
        else if(aux->Livro->id > id) aux = aux->esq;
        else aux = aux->dir;
    }
    return;
}

