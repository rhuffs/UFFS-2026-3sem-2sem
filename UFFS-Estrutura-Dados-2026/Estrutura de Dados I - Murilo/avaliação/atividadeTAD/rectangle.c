#include <stdio.h>
#include "rectangle.h"

retangulo setrectangle(int a, int l){
    retangulo R;
    R.altura = a;
    R.largura = l;
    return R;
}

int calArea(retangulo R){
    int resultado = R.altura * R.largura;
    return resultado;
}

int calPerimeter(retangulo R){
    return 2 * (R.altura + R.largura);
}