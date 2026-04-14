#include <stdio.h>

int log2(int log){
    if (log < 2) return 0;

    else return 1 + log2(log / 2);
}

int main(){
    int n = 55;
    printf("o log de 2 de %d é %d ",n, log2(55));
    return 0;

}