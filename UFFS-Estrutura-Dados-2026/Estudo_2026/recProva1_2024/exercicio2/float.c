#include <stdio.h>

typedef struct vreal
{
    int inteiro;
    int decimal;
}vreal;

vreal setReal(int inteiro, int decimal){
    vreal r;
    r.inteiro = inteiro;
    r.decimal = decimal;
    return r;
}

void showReal(vreal r){
  printf("%d,%d \n",r.inteiro, r.decimal );
  

}

vreal sumReal(vreal *vr1, vreal *vr2){
    vreal vr;
    vr.inteiro = vr1->inteiro + vr2->inteiro;
    if (vr1->decimal + vr2->decimal > 99) {
        vr.inteiro ++;
        vr.decimal = (vr1->decimal + vr2->decimal ) - 100;
    }
    else vr.decimal = vr1->decimal + vr2->decimal;

    return vr;
}

int main(){
    vreal vtr = setReal(3,88);
    showReal(vtr);

    vreal vtr1 = setReal(5,99);
    vreal vtr2 = setReal(3,60);

    showReal(sumReal(&vtr1,&vtr2));
}



