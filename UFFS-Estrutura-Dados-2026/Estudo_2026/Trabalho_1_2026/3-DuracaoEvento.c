#include<stdio.h>
int main () {

    int horas;
    int inicio;
    int fim;
    printf("Digite a hora do inicio do evento:");
    scanf("%d", &inicio);
    printf("Digite a hora do fim do evento:");
    scanf("%d", &fim);

    if (inicio < 0 || inicio > 23 || fim < 0 || fim > 23){
        printf("Valor invalido");
        return 0;
    }

    if (inicio < fim){
        horas = fim - inicio;
        printf("A duração do evento é de %d horas", horas);
        return 0;
    }
    
    if (inicio > fim){
        horas = (24 - inicio) + fim;
        printf("A duração do evento é de %d horas", horas);
        return 0;
    }

}