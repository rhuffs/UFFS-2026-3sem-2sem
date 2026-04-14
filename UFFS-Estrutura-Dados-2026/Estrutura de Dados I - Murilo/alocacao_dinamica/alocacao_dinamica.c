#include <stdio.h>
#include <stdlib.h>

void ponteiro(int *P)
{
    /*isso possibilida a alocação em um endereço de memória*/
    P = /*para lembrar que é um ponteiro (cast)*/ (int *)malloc(sizeof(int)); // ele é um void que ele retorna um endereço com os valores allocados
    scanf("%d", P);/*não colocar o & porque já é um ponteiro*/
    printf("Conteudo do P: %d\n", *P);
    printf("Local de apontamento: %p\n", P);
}

int main()
{
    /*alocação estática: Os espaços para as variáveis são alocados durante o carga do programa para a memória
    Problema: se tivermos que carregar muitos valores para a memória mas não sabemos o máximo?
    poderiamos tentar criar um super vetorsão
    int v[3000] * 4 bytes = 12000 bytes (ou 12 KB)
    */

    // RELEMBRANDO
    /*
        int a;
    float b;
    int v[3];
    a = 10;
    b = 3.1416;
    v[0] = 3;
    v[1] = 4;
    v[2] = 5;
    return 0;
    int a;
    int *p;
    a = 10; //-> memória: 10 -> 20
    p = &a;// -> memória: 10
    *p = 20;// -> armazene o 20 apontado no endereço que ele está apontando
    int v[4] = {2, 4, 6, 8};
    *v = 10;// = {10, 4, 6, 8}; (ponteiro aponta para a casa [0])
    *(v + 1);// = 12 = {10, 12, 6}; (agora aponta para a casa[1])

    */
    int *P; /*tamanho em bytes, não sabemos? utilizar syzeof*/

    ponteiro(*P);
    /*para conseguir fazer com que a gente arrume isso precisamos utilizar a biblioteca <stdlib.h>, para usarmos a função de alocaão dinâmica*/
}