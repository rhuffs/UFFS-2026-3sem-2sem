
#include <stdio.h>
#include <stdlib.h>


typedef struct ListaDupla{
    int valor;
    struct ListaDupla *prev;
    struct ListaDupla *next;
} ld;


ld* insereInicio(ld *head, int valor){
    ld *novo = (ld*) malloc(sizeof(ld));
    novo->valor = valor;
    novo->next = head;
    novo->prev  = NULL;

    if (head != NULL) {
        head->prev = novo;
    }
    return novo;   
}


ld *insereNoMeio(ld *head, int valor, int key){
    ld *novo = (ld*) malloc(sizeof(ld));
    novo->valor = valor;
    novo->next = NULL;
    novo->prev = NULL;

    if(head == NULL){
        return novo;
    }

    ld *aux;

    for(aux = head; aux != NULL; aux = aux->next){
        if(aux->valor == key){

            novo->next = aux->next;
            novo->prev = aux;

            if(aux->next != NULL){      // verifica se não é o último nó
                aux->next->prev = novo;
            }

            aux->next = novo;

            return head;
        }
    }

    free(novo);
    return head;
}


ld *removeNo(ld *head, int key){

    ld *aux;

    if(head == NULL){
        return head;
    }

    for(aux = head; aux != NULL; aux = aux->next){
        if(aux->valor == key)
            break;
    }

    if(aux == NULL){   // não encontrou
        return head;
    }

    // único elemento
    if(aux->prev == NULL && aux->next == NULL){
        free(aux);
        return NULL;
    }

    // primeiro elemento
    if(aux->prev == NULL){
        head = aux->next;
        head->prev = NULL;
        free(aux);
        return head;
    }

    // último elemento
    if(aux->next == NULL){
        aux->prev->next = NULL;
        free(aux);
        return head;
    }

    // elemento do meio
    aux->prev->next = aux->next;
    aux->next->prev = aux->prev;
    free(aux);

    return head;
}