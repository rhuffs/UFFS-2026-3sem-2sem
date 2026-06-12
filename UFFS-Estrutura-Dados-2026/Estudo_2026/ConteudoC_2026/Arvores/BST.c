// Arvore Binaria de Busca
#include <stdlib.h>
#include <stdio.h>

typedef struct Tree{
    int value;
    struct Tree *left, *right;
} Tree;

Tree *insertTree(Tree *root, Tree *node){
    if (root == NULL) return node;
    Tree *aux = root;
    while (aux != NULL){
        if (node->value <= aux->value){ // vai para esquerda
            if (aux->left == NULL){
                aux->left = node;
                break;
                aux=aux->left;
            }
        } else {
            if (node->value >= aux->value){ // vai pra direita pt
                if (aux->right == NULL){
                    aux->right = node;
                    break;
                    aux=aux->right;
                }
            }
        }
    }
    return root;

}


/*===================================================================*/


//recursivo

Tree *recurinsertNode(Tree *node, Tree *root){
    if (root == NULL) return node;

    if (node->value <= root->value){
        root->left = recurinsertNode(root->left,node);
    } else{
        if (node->value >= root->value){
            root->right= recurinsertNode(root->right,node);
        }
    }
}

