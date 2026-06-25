#include <stdio.h>
#include <stdlib.h>

// ------- lista simples -------

struct tsimp {
    int info;
    struct tsimp *next;
};
typedef struct tsimp tsimp;

struct tsentsim {
    tsimp *first;
    tsimp *last;
};
typedef struct tsentsim tsentsim;


void enqueue(tsentsim *fila, int valor){ // versao com sentinela
    tsimp *novo = (tsimp *) malloc(sizeof(tsimp));
    novo->info = valor;
    novo->next = NULL;

    if (fila->first == NULL) {  // fila vazia
        fila->first = novo;
        fila->last  = novo;
    } else {
        fila->last->next = novo;  // liga o último ao novo
        fila->last = novo;        // atualiza o last
    }
}

tsimp *enqueue(tsimp *first, int valor) { // versao sem sentinela
    tsimp *novo = (tsimp*) malloc(sizeof(tsimp));
    novo->info = valor;
    novo->next = NULL;

    if (first == NULL)   // fila vazia
        return novo;

    tsimp *aux = first;
    while (aux->next != NULL)  // para no último nó
        aux = aux->next;

    aux->next = novo;    // liga o último ao novo
    return first;
}

void dequeue(tsentsim *fila){
    if (fila->first == NULL) return;
    tsimp *aux = fila->first;
    fila->first = fila->first->next;
    if (fila->first == NULL) fila->last = NULL;
    free(aux);
}