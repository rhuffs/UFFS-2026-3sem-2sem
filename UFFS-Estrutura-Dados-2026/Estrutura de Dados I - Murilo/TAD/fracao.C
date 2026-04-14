#include <stdio.h>
#include "fracao.h"


fracao setFrac(int n, int d){
    fracao frac;
    frac.num = n;
    frac.den = d;   
    return frac;
}

fracao multiplicacao(fracao vlr1,fracao vlr2){
    fracao result;
    result.num = vlr1.num * vlr2.num;
    result.den = vlr1.den * vlr2.den;
    return result;
}

fracao divisao(fracao vlr1, fracao vlr2){
    fracao result;
    result.num = vlr1.num * vlr2.den;
    result.den = vlr2.den * vlr1.num;

    return result;
}

void showFrac(fracao frac){
    printf("Sua fração é %d/%d", frac.num,frac.den);
}