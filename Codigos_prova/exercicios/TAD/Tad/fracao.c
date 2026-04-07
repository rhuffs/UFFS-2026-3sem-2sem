#include <stdio.h>
#include "fracao.h"


fracao setFrac(int num, int den){
    fracao f;
    f.num = num;
    f.den = den;

    return f;
}

void showFrac(fracao a){
    printf(" numerador  :%d \n denominador:  %d \n ", a.num, a.den);
}

fracao multiFrac(fracao a, fracao b){
    fracao ab;
    ab.num = a.num * b.num;
    ab.den = a.den * b.den;
    return ab;
} 

fracao divFrac(fracao a, fracao b){
    fracao ab;
    ab.num = a.num * b.den;
    ab.den = a.den * b.num;

    return ab;
}

