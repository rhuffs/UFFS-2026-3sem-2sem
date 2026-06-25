#include <stdio.h>
#include <stdlib.h>

typedef struct arvore{
    int valor;
    struct arvore *left;
    struct arvore *right;
    
} arvore;

arvore *insereNaArvore(arvore *raiz,int valor){
    arvore *novo = (arvore *)malloc(sizeof(arvore));
    novo->valor = valor;
    novo->left = NULL;
    novo->right = NULL;
    arvore *aux = raiz;
    if (raiz == NULL){
        return novo;
    } 

    while(1){
        if (valor < aux->valor){
            if (aux->left == NULL){
                aux->left = novo;
                break;
            }
            aux = aux->left;
        } else {
            if(aux->right == NULL){
                aux->right = novo;
                break;
            }
            aux = aux->right;
        }
    }

    return raiz;
}


arvore *removeDaArvore(arvore *raiz, int key) {
    if (raiz == NULL) return NULL;

    if (key < raiz->valor) {
        raiz->left = removeDaArvore(raiz->left, key);

    } else if (key > raiz->valor) {
        raiz->right = removeDaArvore(raiz->right, key);

    } else {  // achou o nó a remover
        // caso 1 e 2 — zero ou um filho
        if (raiz->left == NULL) {
            arvore *aux = raiz->right;
            free(raiz);
            return aux;
        }
        if (raiz->right == NULL) {
            arvore *aux = raiz->left;
            free(raiz);
            return aux;
        }

        // caso 3 — dois filhos
        // acha o menor da subárvore direita (sucessor)
        arvore *aux = raiz->right;
        while (aux->left != NULL)
            aux = aux->left;

        raiz->valor = aux->valor;                         // copia o valor
        raiz->right = removeDaArvore(raiz->right, aux->valor); // remove o sucessor
    }

    return raiz;
}


void inOrder(arvore *raiz){
    if (raiz == NULL) return; //caso base
    inOrder(raiz->left);  // visita esquerda
    printf("%d ", raiz->valor);   // visita raiz
    inOrder(raiz->right);  // visita direita
}

void preOrder(arvore *raiz) {
    if (raiz == NULL) return;
    printf("%d ", raiz->valor); // raiz primeiro
    preOrder(raiz->left);
    preOrder(raiz->right);
}

void postOrder(arvore *raiz) {
    if (raiz == NULL) return;
    postOrder(raiz->left);
    postOrder(raiz->right);
    printf("%d ", raiz->valor); // raiz por último
}

int main() {
    arvore *raiz = NULL;

    // insere os valores
    raiz = insereNaArvore(raiz, 20);
    raiz = insereNaArvore(raiz, 10);
    raiz = insereNaArvore(raiz, 30);
    raiz = insereNaArvore(raiz, 5);
    raiz = insereNaArvore(raiz, 15);
    raiz = insereNaArvore(raiz, 25);
    raiz = insereNaArvore(raiz, 40);

    /*
            20
           /  \
         10    30
        /  \  /  \
       5  15 25  40
    */

    printf("In-order:   ");
    inOrder(raiz);
    printf("\n");
    // saída: 5 10 15 20 25 30 40

    printf("Pre-order:  ");
    preOrder(raiz);
    printf("\n");
    // saída: 20 10 5 15 30 25 40

    printf("Post-order: ");
    postOrder(raiz);
    printf("\n");
    // saída: 5 15 10 25 40 30 20

    return 0;
}