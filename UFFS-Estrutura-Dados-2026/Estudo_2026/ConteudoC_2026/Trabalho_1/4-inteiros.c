#include<stdio.h>
int main () {
    int n1;
    int n2;
    int n3;
    int n4;
    int positivos = 0;
    int negativos = 0;
    printf("Digite o primeiro numero inteiro:");
    scanf("%d", &n1);
    printf("Digite o segundo numero inteiro:");
    scanf("%d", &n2);
    printf("Digite o terceiro numero inteiro:");
    scanf("%d", &n3);
    printf("Digite o quarto numero inteiro:");
    scanf("%d", &n4);   
    int i = 0;
    if (n1 > 0){
        positivos++;
    } else if (n1 < 0){
        negativos++;
    }
    if (n2 > 0){
        positivos++;
    } else if (n2 < 0){
        negativos++;
    }
    if (n3 > 0){
        positivos++;
    } else if (n3 < 0){
        negativos++;
    }
    if (n4 > 0){
        positivos++;
    } else if (n4 < 0){
        negativos++;
    }
    printf("%d [+] e %d [-]", positivos, negativos);
}