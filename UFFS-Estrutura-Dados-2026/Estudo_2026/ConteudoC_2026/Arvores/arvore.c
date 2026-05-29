#include <stdio.h>
#include <stdlib.h>

//Nó ou Vertice - Contem uma informacao util
//Aresta, conexão entre nos.
// Caminho - Sequencia de Nós.


typedef struct Tree{
    int value;
    struct Tree *left, *right;
} Tree;

