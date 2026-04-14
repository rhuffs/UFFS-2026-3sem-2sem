#include <stdio.h>

typedef struct cansado
{
    int inteiro;
    int decimal;
} cansado ;

cansado setReal(int i, int  d){
    cansado c;
    if (d < 0 || d > 99){
         c.inteiro = -1; 
         c.decimal = -1;
    } else {
        c.inteiro = i;
        c.decimal = d;
    }

    return c;
}

void showReal(cansado c){
    printf("%d.%02d", c.inteiro, c.decimal);

}

cansado sumReal(cansado vr1, cansado vr2){
    cansado vr;
    vr.inteiro = vr1.inteiro + vr2.inteiro;
    if (vr1.decimal + vr2.decimal > 99){
        vr.inteiro ++;
        vr.decimal = (vr1.decimal + vr2.decimal) - 100;

    } else {
        vr.decimal = vr1.decimal + vr2.decimal;
    }

    return vr;
}

int main (){
    cansado vr1, vr2, vr3;
    vr1 = setReal(1,70);
    vr2 = setReal(2,45);
    printf("\n");
    showReal(vr1);
    printf("\n");
    showReal(vr2);
    printf("\n");
    vr3 = sumReal(vr1,vr2);
    showReal(vr3);
}