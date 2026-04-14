#include <stdio.h>



int exp(int n, int expo){
    if (expo == 0) return 1;
    if (expo == 1) return expo;

    return n * exp(n, expo -1);
} 

int main (){
 

    printf("%d", exp(2,3));
}