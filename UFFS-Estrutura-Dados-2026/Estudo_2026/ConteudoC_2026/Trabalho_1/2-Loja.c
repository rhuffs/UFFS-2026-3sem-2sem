#include<stdio.h>

int main() {
    float PrecoProduto;
    int FormaPagamento;
    float ValorFinal;

    printf("Digite o valor do produto:");
    scanf("%f", &PrecoProduto);
    printf("Digite a forma de pagamento (1-À vista, 2-Parcelado):");
    scanf("%d", &FormaPagamento);

    if (FormaPagamento == 1){
        ValorFinal = PrecoProduto * 0.95;
        printf("O preço a vista é: R$ %.2f", ValorFinal);
        return 0;
    } else if (FormaPagamento == 2){
        ValorFinal = PrecoProduto * 1.10;
        printf("O preço parcelado é: R$ %.2f", ValorFinal);
        return 0;
    } else {
        printf("Forma de pagamento inválida.");
        return 0;
    }
}