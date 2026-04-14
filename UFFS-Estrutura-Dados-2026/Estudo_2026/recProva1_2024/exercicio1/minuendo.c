#include <stdio.h>

int div(int m,int n){
    if ( m < n) return 0;
    else return 1 + div(m-n , n);
}

int main(){
    int res = div(11,3);
    printf("%d",res);
}