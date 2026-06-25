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




tsentsim *getList (int *v, int tam){
    tsentsim *sentinelas = (tsentsim* )malloc(sizeof(tsentsim));
    sentinelas->first= NULL;
    sentinelas->last = NULL;

    for(int i = 0; i < tam; i++){
        tsimp *novo = (tsimp*) malloc(sizeof(tsimp));
        novo->info = v[i];
        novo->next = NULL;


        if (sentinelas->first == NULL){
            sentinelas->first = novo;
            sentinelas->last = novo;
        } else {
            sentinelas->last->next = novo; // o proximo do ultimo recebe o nó
            sentinelas->last = novo; // e o last aponta pro ultimo
        }
    }

    return sentinelas;
}


