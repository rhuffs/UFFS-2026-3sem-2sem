//EXERCICIO 1
#include <stdio.h>
#include <stdlib.h>

struct tsimp {
    int info;
    struct tsimp *next;
};
typedef struct tsimp simples;


struct tsentsimp {
    simples *first;
    simples *last;
};
typedef struct tsentsimp sents;

sents *getlist(int *v, int tam){
    int i;
    simples *P;

    sents *sentinelas = (sents *)malloc(sizeof(sents));
    
    sentinelas->first = NULL;
    sentinelas->last = NULL;
    simples *aux = NULL;
    for(i = 0; i < tam; i++){
        P = (simples *)malloc(sizeof(simples));
        P->info = v[i];
        P->next = NULL;
        if(sentinelas->first == NULL){
            sentinelas->first = P;
            aux = P;
        }
        aux->next = P;
        aux = aux->next;
    }
    sentinelas->last = aux;
    return sentinelas;
}

struct tdup {
    float info;
    struct tdup *next, *prev;
};
typedef struct tdup dupla;

struct tsentdup {
    dupla *first;
    dupla *last;
};
typedef struct tsentdup sentd;

sentd *getinter(sents s1, sents s2){
    sentd *resultado = (sentd *)malloc(sizeof(sentd));
    resultado->first = NULL;
    resultado->last = NULL;
    simples *aux1;
    simples *aux2;
    dupla *new;
    for(aux1 = s1.first; aux1 != NULL; aux1 = aux1->next){
        for(aux2 = s2.first; aux2 != NULL; aux2 = aux2->next){
            if(aux1->info == aux2->info){
                new = (dupla *) malloc(sizeof(dupla));
                new->info = aux1->info;
                new->next = NULL;
                new->prev = NULL;
                if(resultado->first == NULL){
                    resultado->first = new;
                    resultado->last = new;
                }
                resultado->last->next = new;
                new->prev = resultado->last;
                resultado->last = new;

                break;
            }
        }
    }
    return resultado;
}