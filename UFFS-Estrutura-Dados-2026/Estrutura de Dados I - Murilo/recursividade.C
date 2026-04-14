#include <stdio.h>

int fatorial(int);

int expoente(int, int);

int somatoria(int [], int);

int mdc(int, int);

int log(int);

int main(){
    printf("%d\n",fatorial(4)) ;

    printf("%d\n",expoente(2,3));

    int vetor[] = {4, 3, 5, 7};
    int tamanho = 4;
    printf("%d\n", somatoria(vetor, tamanho));

    printf("%d\n", mdc(12, 18));

    printf("%d", log(64));
    return 0;
}

int log(int n){
    if(n <= 1 ) return 0;
    return 1 + log(n/2);
}
int mdc(int m, int n){
    if (n == 0) return m;
    return mdc(n, m%n);
}

int somatoria(int v[], int n){
    if (n == 0) return v[0];
    return v[n] + somatoria(v, n -1);
}

int expoente(int num, int exp){
    if (exp == 0) return 1;
    if (exp == 1) return num;

    return num * expoente (num, exp - 1);

}

int fatorial(int n){
    if (n == 0 || n == 1) return 1;

    return n * fatorial(n-1);
}