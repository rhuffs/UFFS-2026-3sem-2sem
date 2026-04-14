#include <stdio.h>
#include "fracao.h"


fracao setFrac(int num, int den){
    fracao f;
    f.num = num;
    f.den = den;
}

void showFrac(fracao a){
    printf("%d \n _ \n %d", a.num, a.den);
}

fracao multiFrac(fracao a, fracao b){
    fracao ab;
    ab.num = a.num * b.num;
    ab.den = a.den * b.den;
    showFrac(ab);
    return ab;
} 

fracao divFrac(fracao a, fracao b){
    fracao ab;
    ab.num = a.num * b.den;
    ab.den = a.den * b.num;

    return ab;
}

