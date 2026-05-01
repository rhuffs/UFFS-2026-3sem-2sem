#include <stdio.h>
#include <stdlib.h>
#include "grimorio.h"
#include <string.h>

Grimorio *cria_grimorio(){
    return NULL;
}

Grimorio *aprende_feitico(Grimorio *g, char *nome, int poder_magico){
    Grimorio *novo_feitico = NULL;
    novo_feitico = (Grimorio *)malloc(sizeof(Grimorio));
    novo_feitico->poder_magico = poder_magico;
    strcpy(novo_feitico->nome_feitico , nome);
    novo_feitico->next = NULL;
    if (g == NULL ) return novo_feitico;
    novo_feitico->next = g;
    return novo_feitico;
}

// void lista_feitico(Grimorio *g){
//     Grimorio *aux =  NULL;
//     int i = 0;
//     for (aux = g; aux != NULL; aux = aux->next){
//         for(i = 0; i<20; i++ ){
//             printf("%s", aux->nome_feitico[i]);
//         }
//         printf("%d\n", aux->poder_magico);
//     }
// }

void lista_feitico(Grimorio *g){
    if (g == NULL) return;
    lista_feitico(g->next);
    printf("%d %s\n",g->poder_magico,g->nome_feitico);
}

