#include <stdio.h>

typedef struct triangulo
{
    int A , B , C;
} triangulo;

triangulo setTria(int a, int b , int c){
    triangulo t;
    t.A = a;
    t.B = b;
    t.C = c;
    return t;
}

int isTriangle(triangulo t){
    if (t.A + t.B > t.C && t.B + t.C > t.A && t.A + t.C > t.B) return 1;
    else return 0;
    
}



int main(){
    triangulo trg;
    trg = setTria(16,20,30);
    isTriangle(trg);
    if (isTriangle(trg)) printf("é um triangulo valido");
    else printf ("Nao é valido");


}