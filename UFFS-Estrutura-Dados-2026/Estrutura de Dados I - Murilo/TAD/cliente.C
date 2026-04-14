#include <stdio.h>
#include "fracao.h"

int main()
{
    fracao valor1 = setFrac(10, 2);
    showFrac(valor1);
    printf("\n");
    fracao valor2 = setFrac(15,5);
    showFrac(valor2);
    showFrac(multiplicacao(valor1, valor2));
    showFrac(divisao(valor1, valor2));

    return 0;
}
//primeiro: gcc -Wall -C programa.C -> sem a main
//segundo: gcc -Wall programacomamain.C programa2comasfuncoes.o nome para o programa
//                   (aqui é o que tem a main)
//terceiro: ./