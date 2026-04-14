#include <stdio.h>

typedef struct Triangle
{
    int A, B, C;

} Triangle; 

Triangle setTria(int a, int b, int c){
    Triangle trg;
    trg.A = a;
    trg.B = b;
    trg.C = c;
    return trg;
}

int isTriangle(Triangle trg){
   if (trg.A + trg.B > trg.C && trg.B + trg.C > trg.A && trg.A + trg.C > trg.B ){
    return 1;
   } else {
    return 0;
   }
}

int main (){
    Triangle t = setTria(2,5,7);
    int Resutado = isTriangle(t);
    if (Resutado == 1){
        printf("é um triangulo");

    }else {
        printf("Nao é um Triangulo");
    }
}
