#include <stdio.h>

typedef struct 
{
    float largura;
    float altura;
}retangulo;

retangulo criarRet(float A, float L){
    retangulo r;
    r.altura = A;
    r.largura = L;

    return r;
}

void calcArea(retangulo r){
    float area = 0;
    area = r.altura * r.largura;
    printf("%.2f \n",area );

}

void calcPerim(retangulo r){
    float perim = 0;
    perim = (r.altura * 2) + (r.largura * 2) ;
    printf("%.2f \n",perim );

}

int main(){
    retangulo a;
    a.altura = 2;
    a.largura = 5;
    calcArea(criarRet(2,5));
    calcPerim(a);
}


