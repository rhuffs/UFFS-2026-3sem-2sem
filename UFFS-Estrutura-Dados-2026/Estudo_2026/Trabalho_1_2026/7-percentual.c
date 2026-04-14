#include <stdio.h>

int main (){
    int num = 1;
    float resultado;
    int certo = 0;
    int total = 0;
    while (num != 0){

        printf("Digite um numero: ");
        scanf("%d", &num);
        if (num >= 10 && num <= 20){
            certo = certo + 1;
            total++;

        } else if (num != 0 ) {
            total++;
        }
    }
    

    resultado = ((float)certo / total) * 100;

    printf("Porcentagem entre 10 e 20 ""%.2f""%%", resultado);
    return 0; 

}




