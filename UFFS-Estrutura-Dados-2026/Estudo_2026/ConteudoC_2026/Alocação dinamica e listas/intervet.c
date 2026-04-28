#include <stdio.h>
#include <stdlib.h>

typedef struct value{
    int valor;
    struct value *next;
}value;

int *intersecValue(value *v1, value *v2, int *tam){
    int capacidade = 10;
    int *vet = malloc(capacidade * sizeof(int));
    value *aux, *aux2;
    int i = 0;

    for(aux = v1; aux != NULL; aux = aux->next){
        for(aux2 = v2; aux2 != NULL; aux2 = aux2->next){
            if(aux->valor == aux2->valor){

                // cresce o vetor se necessário
                if(i >= capacidade){
                    capacidade *= 2;
                    vet = realloc(vet, capacidade * sizeof(int));
                }

                vet[i++] = aux->valor;
                break; // evita duplicar se o mesmo valor aparecer várias vezes em v2
            }
        }
    }

    *tam = i;
    return vet;
}   