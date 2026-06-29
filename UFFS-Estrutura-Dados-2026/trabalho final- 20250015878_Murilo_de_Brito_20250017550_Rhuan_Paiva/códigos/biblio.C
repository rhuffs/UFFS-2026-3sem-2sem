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
        if(pai->Livro->id > Livro->id) pai->esq = NewL;
        else pai->dir = NewL;
        return raizL;
    }
}

Books *findBook(NoBooks *raiz, int id){
    NoBooks *aux = raiz;
    while(aux != NULL){
        if(id == aux->Livro->id) return aux->Livro;
        else if(aux->Livro->id > id) aux = aux->esq;
        else aux = aux->dir;
    }
    return;
}

// Encontrar extremo (mínimo ou máximo)
NoBooks *ExtremeBook(NoBooks *raizL, int buscarMinimo) {
    if (raizL == NULL) return NULL;
    NoBooks *aux = raizL;
    if (buscarMinimo)  while (aux->esq != NULL) aux = aux->esq;
    else while (aux->dir != NULL) aux = aux->dir;
    return aux;
}

// Gerar próximo ID automaticamente
int nextIDbook(NoBooks *raizL) {
    if (raizL == NULL) return 1;//1 = mínimo
    NoBooks *maior = ExtremeBook(raizL, 0);  // 0 = máximo
    return maior->Livro->id + 1;
}

//remover os Livros
NoBooks *removeBook(NoBooks *raiz, int id) {
    if (raiz == NULL) {
        printf("!!ERROR!!\n>Livro com ID (%d) não encontrado.\n", id);
        return NULL;
    }

    if (id < raiz->Livro->id) raiz->esq = removeBook(raiz->esq, id);
     else if (id > raiz->Livro->id) raiz->dir = removeBook(raiz->dir, id);
     else {
        if (raiz->esq == NULL) {
            NoBooks *aux = raiz->dir;
            free(raiz->Livro);  
            free(raiz);         
            return aux;
        }
        if (raiz->dir == NULL) {
            NoBooks *aux = raiz->esq;
            free(raiz->Livro);  
            free(raiz);         
            return aux;
        }
        
        NoBooks *aux = raiz->dir;
        while (aux->esq != NULL) {
            aux = aux->esq;
        }
        
        Books *livroTemp = raiz->Livro;
        raiz->Livro = aux->Livro;
        aux->Livro = livroTemp;
        
        raiz->dir = removeBook(raiz->dir, aux->Livro->id);
    }
    
    return raiz;
}

//listar os livros->in order
void ListBooks(NoBooks *Rail){
    if(Rail == NULL) return;

    ListBooks(Rail->esq);
}