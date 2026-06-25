#include <stdio.h>
#include <stdlib.h>

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



tsentsim* getInter(tsentsim *s1, tsentsim *s2) {
    tsentsim *resultado = (tsentsim*) malloc(sizeof(tsentsim));
    resultado->first = NULL;
    resultado->last  = NULL;

    tsimp *a = s1->first;

    while (a != NULL) {
        tsimp *b = s2->first;

        while (b != NULL) {
            if (a->info == b->info) {
                tsimp *novo = (tsimp*) malloc(sizeof(tsimp));
                novo->info = a->info;
                novo->next = NULL;

                if (resultado->first == NULL) {
                    resultado->first = novo;
                    resultado->last  = novo;
                } else {
                    resultado->last->next = novo;
                    resultado->last = novo;
                }
                break; 
            }
            b = b->next;
        }
        a = a->next;
    }

    return resultado;
}