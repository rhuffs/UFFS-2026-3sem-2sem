#include<stdio.h>

#define MAX 100

typedef struct {
    int vet[MAX];  // o vetor que armazena os elementos
    int size;      // quantidade de elementos atual
} Heap;

int pai(int i)        { return (i - 1) / 2; }
int filho_esq(int i)  { return 2 * i + 1;   }
int filho_dir(int i)  { return 2 * i + 2;   }

void maxheap(Heap *heap,int valor){
    heap->vet[heap->size] = valor;
    heap->size++;

    int i = heap-> size - 1;
    
    while(i > 0 && heap->vet[i] > heap->vet[pai(i)]){
        int aux = heap->vet[i];
        heap->vet[i] = heap->vet[pai(i)];
        heap->vet[pai(i)] = aux;
        i = pai(i);
    }
}