#include <stdio.h>

int soma_digitos(int n){
    if(n<10) return n;
    return n%10 + soma_digitos(n/10);
}


int main(){
    int n = 1234;
    printf("%d",soma_digitos(n));
}