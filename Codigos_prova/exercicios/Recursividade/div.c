#include <stdio.h>


int div(int n){
    if (n <= 1) return 0;
    else return 1 + div(n/2);
}


int main(){
    printf("%d", div(100));
}