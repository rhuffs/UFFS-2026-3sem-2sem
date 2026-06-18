#include <stdio.h>

// Existe uma prioridade dos elementos na fila
// Não obedece a estratégia FIFO
// Operações
//      ->Inserir obedecendo a prioridade
//      ->Remover o elemento com maior prioridade
// Ideia
//      ->Organizar a fila colocando o elemento de maior prioridade na frente

/*Heap
    -> encherga um vetor como uma árvore
    -> organiza a árvore
    -> encontra os filhos e os pais de um objeto/ vetor
    -> Se escolher menor: min-heap (menor valor está na raiz)
    -> Se escolher maior: max-heap (maior valor está na raiz)
    -> Não confundir com a árvore binária de busca
    -> No computador será uma memória, mas, em nossa cabeça, será uma árvore

Vetor
    -> Cada posição do vetor é considerada pai de outras duas posições
    -> A posição i passa a ser pai das posições
        -> 2i+1 → filho da esquerda
        -> 2i+2 → filho da direita
        -> (i-1)÷2 (int) → pai

*/


#define SIZE 100

struct THeap{
   int heap[SIZE];
   int size;
};typedef struct THeap Heap;

//FUNÇÕES
//RETORNA O PAI
int parent(i){ return (int) (i-1)/2;}
//retorna o irmão a esquerda
int left(i){return 2 * i+1;}
//retorna o irmão a direita
int right(i){return 2* i+1;}

void swap(int *a, int *b){
    int temp = *a;
    *a = *b;
    *b = temp;
}

void insertion(int ent, Heap *H){
    int pai;
    H->heap[H->size] = ent;
    int i = H->size;
    H->size ++;
    if(i == 0) return;
    else{
        while(i>0){
            pai = (i-1)/2;
            if(H->heap[i] > H->heap[pai]){
                swap(&H->heap[i], &H->heap[pai]);
                i = pai;
            } else break;
        }
    }
}