#include <stdio.h>
#include <math.h>

typedef struct {
    int x;
    int y;
} ponto;

ponto iniciaPonto(int x, int y){
    ponto p;
    p.x = x;
    p.y = y;

    return p;
}

float distanciaPonto(ponto a, ponto b){
    int dx, dy;
    dx = b.x - a.x;
    dy = b.y - a.y;
    float Dab;
    Dab = sqrt(dx*dx + dy*dy);
    return Dab;
}

int main(){
    printf("%.2f", distanciaPonto(iniciaPonto(1,3), iniciaPonto(5,6)));
}