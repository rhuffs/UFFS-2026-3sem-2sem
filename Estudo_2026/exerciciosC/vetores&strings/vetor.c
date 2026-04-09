#include <stdio.h>

/*Escreva uma função que:

receba um vetor de inteiros
retorne a soma de seus elementos*/

int sumVet(int vet[], int tamanho){//é preciso passar o tamanho, pois usar sizeof dentro da funcao nao funciona pois o vet vira ponteiro

    int sum = 0;
    for(int i = 0; i < tamanho; i++){
        sum += vet[i];
    }

    return sum;
}

int main(){
    int vetor [5 ] = {3 ,4, 6, 8, 3};
    int tamanho = sizeof(vetor) / sizeof(vetor[0]); //divite o valor em bytes do vetor inteiro, pelo valor em bytes de uma posicao do vetor, assim temos quantos elementos tem o vetor
    printf("%d",sumVet(vetor, tamanho));
}