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


// ------- lista dupla -------

struct tdup {
    float info;
    struct tdup *next;
    struct tdup *prev;
};
typedef struct tdup tdup;

struct tsentdup {
    tdup *first;
    tdup *last;
};
typedef struct tsentdup tsentdup;



tsentsim* getList(int *v, int tam) {
    tsentsim *sents = (tsentsim*) malloc(sizeof(tsentsim));
    sents->first = NULL;
    sents->last  = NULL;

    for (int i = 0; i < tam; i++) {
        tsimp *novo = (tsimp*) malloc(sizeof(tsimp));
        novo->info = v[i];
        novo->next = NULL;

        if (sents->first == NULL) {
            sents->first = novo;
            sents->last  = novo;
        } else {
            sents->last->next = novo;  // liga o último ao novo
            sents->last = novo;        // atualiza o last
        }
    }

    return sents;
}