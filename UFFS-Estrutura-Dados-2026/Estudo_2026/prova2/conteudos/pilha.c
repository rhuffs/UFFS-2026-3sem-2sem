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


void *push(tsentsim *pilha, int valor){
    tsimp *novo = (tsimp *)malloc(sizeof(tsimp));
    novo->info = valor;
    novo->next = pilha->first;
    pilha->first = novo;

    if (pilha->last == NULL){
        pilha->last = novo;
    }
}

void pop(tsentsim *pilha){
    if(pilha->first == NULL) return;
    tsimp *aux = pilha->first;

    pilha->first = pilha->first->next; // o primeiro da pilha recebe o proximo do primeiro da pilha, agr da pra liberar o aux sem peder o primeiro.
    if (pilha->first == NULL){
        pilha->last == NULL;
    }
    free(aux);
}

