#include <stdio.h>
#include <stdlib.h>

// Módulo de funções
int algumacoisa(int a, int b)
{
    return a + b; // Precisa exclusivamente do return
}

int soma2(int n1, int n2)
{
    return n1 + n2;
}

//void Teste(int a, int b) { a + b; } // Obrigatório não ter retun

// a função pode estar tanto em cima da main, quanto embaixo, mas, precisa primeiro criar
// um protótipo da função, Exemplo:

int elevaAoquadrado(int); // não precisa colocar o nome de uma variável, só a quantidade de tipos que
                          // serão utilizados na função

// evitar ao máximo utilizar os printf() dentro das funções

float parafahenheit(float C)
{
    return (9 * C / 5) + 32;
}

float paracelcius(float);

void inc1 (int *v){
   (*v)++;
}
void troca(int *A, int *B){
    int aux;
    aux = *A;
       
    *A = *B;
    *B = aux;
}



int main()
{
    //AULA 2
                    // PONTEIRO //
            //-----------------------//
    int a, *b;

    a = 10;
    printf("%i\n %p\n", a, &a); // &a: endereço da variável
    b = &a;                     // assim, o ponteiro será capaz de armazenar o Endereço de A
    printf("%d %p\n", a, b);
    *b = 15; // apontando o 15 em um endereço
    printf("%d %d", a, *b);
          //a variável *c se refere a uma variável que armazena endereços, para armazena-la: c= &avariavelquequeriaadicionar
    char *c, c1 = 'A';//apostrofe é para caracter, aspas simples é para caractere
    c = &c1;
    for (int i = 0; i < 1; i++)
    {
        printf("%c", c[i]);
    }
    //AULA 2/3
                    // FUNÇÕES //
            //-----------------------//

    //-> blocos de comando para organizar o teu código
    //-> precisa se atentar as entradas para as funções e o retorno

    int z = 5, q = 6;
    int pica = soma2(z, q);

    printf("\n%d", pica); // ou printf("\n%d", soma2(a,b));
    //-> como resolveria para resolver 3 números com essa mesma função? curta

    int n5 = soma2(soma2(z, q), 3);
    printf("\n%d", n5);
    // exercícios:

    // questão 4

    float celcius, fahenreit;
    int escolha;
    printf("Escolha entre Celcius ou fahenheit: 1 para celcius, 2 para fahenheit");
    scanf("%i", &escolha);
    if (escolha == 1)
    {
        printf("Qual a temperatura em graus celcius?");
        scanf("%f", &celcius);
        printf("\n%.2f", parafahenheit(celcius));
    }
    if (escolha == 2)
    {
        printf("Qual a temperatura em Fahenreit?");
        scanf("%f", &fahenreit);
        printf("%.2f", paracelcius(fahenreit));
    }

    //-> PARAMETROS//
    //Passagem por cópia:
    //É a forma padrão: copia o valor da tua variável, para uma variável distinta
    //Por referência:
    //Ela não mexe com os meus dados, mas, tem como mexer com as variáveis, utilizando o & para enviar no ENDEREÇO,
    //para enviar um valor direto na memória, seria: int soma2(int *N1), com o *
      int n=10;
    inc1(&n);
    printf("%d",n);
    
    int r = 5, t = 10;
    printf("a = %d, b = %d \n", r, t);
    troca(&r,&t);
    printf("minha vó é\n r = %d, t = %d", r, t);
    return 0;
}

int elevaAoquadrado(int val) { return val * val; }

float paracelcius(float F){
    return 5*(F - 32)/9;
}

