#include <stdio.h>
#include <stdlib.h>

typedef struct Type_dado{
    int dado;
} Dado;

struct Tnos{
    Dado valor;
    struct Tnos *next, *prev;
}; typedef struct Tnos NOS;

struct sentinelas{
    NOS *head, *tail;
}; typedef struct sentinelas sent;

void registrar(sent *S){
    S->head = NULL;
    S->tail = NULL;
}

void insert_fim(sent *s, int dadoN){
    NOS *P = (NOS *)malloc(sizeof(NOS));
    P->valor.dado = dadoN;
    P->next = NULL;
    P->prev = NULL;
    if(s == NULL) return;
    s->tail->next = P;
    P->prev = s->tail;
    return P;
}

void insert_comeco(sent *s, int dadoN){
    NOS *P = (NOS *)malloc(sizeof(NOS));
    P->valor.dado = dadoN;
    P->next = NULL;
    P->prev = NULL;
    if(s == NULL) return;
    s->tail->prev = P;
    P->next = s->tail;
}