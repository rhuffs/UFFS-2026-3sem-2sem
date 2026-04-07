#include <stdio.h>

void alteraValor (int *p){
    *p = 50;
}


int main(){
    int a = 10;
    alteraValor(&a);
    printf("%d", a);
}
