#include <stdio.h>
#include "Retangle.h"


Ret setRet(int l, int a){
    Ret r;
    r.lado = l;
    r.altura = a;// ouuu  Ret r = {l,a};
    return r;
}


int getArea(Ret r){
    return r.lado * r.altura;
}


int getPerim(Ret r){
    return (r.altura + r.lado ) * 2;
}



