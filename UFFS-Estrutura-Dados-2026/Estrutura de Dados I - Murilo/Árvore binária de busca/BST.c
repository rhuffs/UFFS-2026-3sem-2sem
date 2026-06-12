#include <stdio.h>
#include <stdlib.h>

//Árvore de busca
// As árvores binárias são árvores que os nós possuem no máximo 2 filhos
// Devem possuir os atributos que representam o conteúdo do nó + dois ponteiros para os filhos


typedef struct node{
    int value;
    struct node *left, *right;
} Tree;

/*====================================================================*/

//auxiliar
// Tree *insertTreecomauxilio(Tree *root, Tree *no){
//     if(root == NULL) return no; 
//     else{
//         Tree *aux = root;
//         Tree *ant;
//         while (aux != NULL){
//             ant = aux;
//             if(aux->value > no->value) aux = aux->left;
//             if(aux->value < no->value) aux = aux->right;    
//         }
//         if(ant->value > no->value) ant->left = no;
//         if(ant->value < no->value) ant->right = no;
//     }
// }

//também

Tree *iniciano(int V){
    Tree *p = (Tree *)malloc(sizeof(Tree));
    p->value = V;
    p->left = NULL;
    p->right = NULL;
}

/*====================================================================*/
// sem auxilio
Tree *insertTreesemauxilio(Tree *root, Tree *no){
    if(root == NULL) return no; 
    else{
        Tree *aux = root; //---> sem variável extra
        while (aux != NULL){
            if(aux->value > no->value) {
                if(aux->left == NULL) {aux->left = no; break;}
                aux = aux->left;
            }
            else{
                if(aux->right == NULL) {aux->right = no; break;}
                aux = aux->right;
            }    
        }
    }
    return root;
}
// aqui, ele verifica na hora da condição o próximo

/*==========================================================================*/

//recursivo

Tree *insertrecursivo(Tree *root, Tree *no){
    if(root == NULL) return no;
    if(no->value < root->value) root->left = insertrecursivo(root->left, no);
    else                        root->right = insertrecursivo(root->right,no);
}

/*======== ACHAR A KEY ========*/

Tree *getNode(Tree *r, int key){
    if(r== NULL) return NULL;
    if(r->value == key) return r;
    if(key < r->value) return getNode(r->left, key);
    else               return getNode(r->right,key);
}


