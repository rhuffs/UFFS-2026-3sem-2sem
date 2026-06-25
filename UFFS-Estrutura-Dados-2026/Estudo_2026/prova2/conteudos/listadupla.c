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