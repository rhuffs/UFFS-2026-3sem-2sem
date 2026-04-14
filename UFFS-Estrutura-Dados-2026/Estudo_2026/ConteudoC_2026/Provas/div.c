#include <stdio.h>

int div(m,n){
    if (m < n){
        return 0;
    } else {
        return 1 + div(m - n, n );
    }
}

int main (){
    int m, n;
    m=30 ; n = 3;
    
    int resultado = div(m,n);
    printf("%d", resultado);
}