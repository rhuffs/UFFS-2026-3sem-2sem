#include <stdio.h>

int main()
{
    float Precoproduto;
    int FormaPagamento;

    printf("Preço do produto: ");
    scanf("%f", &Precoproduto);
    printf("Forma de Pagamento: \n1 para a vista\n2 para a prazo \n");
    scanf("%i", &FormaPagamento);

    if (FormaPagamento == 1)
    {
        float desconto = Precoproduto * 0.05;
        Precoproduto -= desconto;
        printf("\nPreço a vista: %.2f", Precoproduto);
    }
    else
    {
        float acrescimo = Precoproduto * 0.10;
        Precoproduto += acrescimo;
        printf("\nPreço a prazo: %.2f", Precoproduto);
    }
    return 0;
}