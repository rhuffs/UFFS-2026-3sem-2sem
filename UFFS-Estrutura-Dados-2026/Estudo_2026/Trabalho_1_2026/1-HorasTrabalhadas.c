#include <stdio.h>
int main () {
        
    int horas;
    float Vhoras;
    float salario;
    printf("Digite suas horas Trabalhadas");
    scanf("%d", &horas);
    printf("Digite o valor da hora");
    scanf("%f", &Vhoras);

    salario = horas * Vhoras;

    if (salario <= 0){
        printf("Valor invalido");
        return 0;
    } 

    if (horas > 200) {
        salario = salario * 1.05;
        printf("Seu salario é de R$ %.2f", salario);
        return 0;
    } else {
        printf("Seu salario é de R$ %.2f", salario);
        return 0;
    }


    

}