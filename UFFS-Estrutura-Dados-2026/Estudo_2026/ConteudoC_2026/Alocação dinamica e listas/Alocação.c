#include <stdio.h>
#include <stdlib.h>


int main(){
    /*uso de ponteiros*/
    /*
    int a;
    int *p;
    a = 10;
    p=&a; /*p aponta para endereço de a*/
    //*p = 20;/*o valor do endereco apontado por p recebe 20*/
    //int b =11;
    //p=&b; // p esquece onde estava a
    //vetor é um ponteiro disfarçado
    //int v[4] = {2,4,6,8};
    //*v=10;
    //*(v+1) = 12

    //stdlib serve oara alocacao dinamica de memoria

    //int *p = NULL;
    //inicializar um ponteio apontando para null

    /*funcoes do stdlib
    NULL
    malloc*/
    //if (*p == NULL);
    //p = (int*)/*->cast*/malloc(sizeof/*tamanho de */(int)/*inteiro*/); //importante
    //*p =10;
    //exemplo

    int *p;
    p= (int *)malloc(sizeof(int));
    *p = 22;
    printf("conteudo de p: %d\n",*p);
    printf("local de apontamento: %p\n",p);
    //scanf sem o &

    scanf("%d",p);
}