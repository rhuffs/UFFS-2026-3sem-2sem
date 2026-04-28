#include <stdio.h>
#include <stdlib.h>

typedef struct value
{
    int valor;
    struct value *next;
}value;

value *vetCad(value *f, int vet[], int tam){
    value *aux = NULL, *novo = NULL;
    int i;

    for(i = 0; i < tam; i++){
        novo = (value *)malloc(sizeof(value));
        novo->valor = vet[i];
        novo->next = NULL;

        if(f == NULL){
            f = novo;
            aux = novo;
        } else {
            aux->next = novo;
            aux = novo;       
        }
    }

    return f;
}

int main(){
    value *f = NULL, *aux;
    
    int vet[] = {10, 20, 30, 40, 50};
    int tam = 5;

    f = vetCad(f, vet, tam);

    printf("Lista:\n");
    for(aux = f; aux != NULL; aux = aux->next){
        printf("%d -> ", aux->valor);
    }
    printf("NULL\n");

    // liberar memória
    while(f != NULL){
        aux = f;
        f = f->next;
        free(aux);
    }

    return 0;
}