#include <stdio.h>
#include <stdlib.h>



//Questao 1
typedef struct list{
    int valor; 
    struct list *next;
} list; 

list *getListFromMatriz(int row, int col, int m[row][col]) {list *l, *aux, *first = NULL; for(int r = 0; r < row; r++){for(int c = 0; c< col; c++){l=(list*)malloc(sizeof(list)); l->valor = m[r][c];l->next=NULL;if(first == NULL){first = l;aux=l;}else{aux->next = l;aux = l;}}}return first;}   

list *getNext(list *f, int v){ // 2 questao
    list *aux;
    for (aux = f; aux != NULL; aux = aux->next){
        if (aux->valor == v){
            break;
        }
        if (aux == NULL){
            return NULL;
        }
        return aux->next;
    }
}


list *deleteFirst(list *f, int v){ // quarta questao
    list *aux;
    if (f->valor != v){
        printf("%d não é o primeiro valor\n", v);
        return f;
    }
    aux = f;
    f = f->next;
    free(aux);
    return f;
}


//QUINTA questao



int main(){int matriz[3][3] = {{2,3,4},{4,5,6},{3,4,5}}; getListFromMatriz(3,3,matriz);return 0;}
