#include <stdio.h>
#include <string.h>

// fazer uma função que consiga checkar se ela é palindroma, sem string.h
// retorne 1 se for palindromo, 2 se não for

int ispalindromo(char p[])
{
    int len = 0;
    while (p[len] != '\0'){
        len++;
    }
    int inicio = 0;
    int fim = len - 1;
    while (inicio < fim){
        if(p[inicio]!= p[fim]){
            return 2;
        }
        inicio ++;
        fim --;
    }
    return 1;
}

void vogaisN(char ni[]){
    int tam = 0;
    while(ni[tam] != '\0'){
        if(ni[tam] == 'a') ni[tam] = '4';
        else if(ni[tam] == 'e') ni[tam] = '3';
        else if(ni[tam] == 'i') ni[tam] = '1';
        else if(ni[tam] == 'o') ni[tam] = '0';
        tam ++;
    }

    
}

void inverteVetor(char ni[]){
    int tam = 0;
    while(ni[tam] !='\0'){
        tam ++;
    }
    int inicio = 0;
    int fim = tam - 1;
    char temp; //swap

    while(inicio < fim){
        temp = ni[inicio];
        ni[inicio] = ni[fim];
        ni[fim] = temp;

        inicio ++;
        fim --;
    }

}

int rifa(int ni[], int tam, int VS){
    int soma = 0;
    for(int i = 0; i < tam; i++){
        if(ni[i] == VS) soma++;
    }

    if(soma == 2) return 1;
    else return 0;
}
int main()
{

    char pa[30] = "piraciqueia";
    printf("%d", ispalindromo(pa));

    vogaisN(pa);

    printf("\n%s", pa);

    char pi[20] = "arrop";

    inverteVetor(pi);

    printf("\n%s", pi);
    

    int sort[] = {1,5,2,7,0};

    int tamanho = 5;
    int numero_sorteado = 2;
    printf("\n%d", rifa(sort, tamanho, numero_sorteado));

    return 0;
}

