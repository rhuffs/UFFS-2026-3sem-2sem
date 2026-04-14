#include<stdio.h>
int main (){
    float SumSalario = 0 ;
    int SumFilhos;
    float salario;
    int filhos;
    int ContagemSalario = 0;
    int ContagemFilho = 0;
    float MediaSal;
    float MediaFil;
    
    while (1){
        printf("Digite o salario :");
        scanf("%f", &salario);
        if (salario >= 0){
            SumSalario = SumSalario + salario;
            ContagemSalario++;
        } else {
            break;
        }
        printf("Quantos filhos :");
        scanf("%d", &filhos);
        SumFilhos = SumFilhos + filhos;
        if (filhos > 1)
        {
            ContagemFilho ++;
        }
        


    }

    MediaSal = SumSalario / ContagemSalario;
    MediaFil = SumFilhos / ContagemFilho;

    printf("Media salario :%.2f\nMedia Filhos :%.0f", MediaSal, MediaFil );
}