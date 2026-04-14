#include<stdio.h>
int main (){
    int fatorial;
    int resultado = 1;
    int i;
    printf ("Digite Um numero para saber o fatorial;");
    scanf(" %d", &fatorial);

    

    for (i = fatorial ; i >1 ; i--){
        resultado = resultado * i;

    }

    printf("O Resultado é %d", resultado);
 

}