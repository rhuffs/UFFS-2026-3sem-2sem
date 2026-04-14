
// 📌 1. Ponteiros e Endereçamento (Teoria)
// 1) Explique a diferença entre: valor de uma variável e endereço de memória de uma variável.
// No C, qual operador é usado para obter o endereço?
// R:valor de variável - um tipo de valor(foda-se)
// R:é aonde esse valor estará no espaço da memória
// R:&

// 2) Dado o código abaixo: int x = 10; int *p = &x;
// Responda: a) O que está armazenado em p? b) O que retorna *p? c) O que acontece se fizer *p = 20?
// R:a) o endereço de x
// R:b)20
// R:c)p = 20 e x = 20

// 📌 2. Ponteiros e Funções
// 3) Analise o código:
// void altera(int x) {
//  x = 50;
//}
// int main()
//{
//  int a = 10;
//  altera(a);
//  printf("%d", a);
//}
// a) Qual será a saída? b) Por quê?
// R: a) 10, pq ele enviou uma cópia

// 4) Reescreva a função acima usando ponteiros para que a variável a seja realmente alterada.
// R:
// void altera(int *x){
//    *x = 50;
// }

// int main()
// {
//     int a = 10;
//     altera(&a);
//     printf("%d", a);
// }

// 📌 3. Passagem de Parâmetros
// 5) Diferencie: passagem por valor e passagem por referência. Dê um exemplo simples em C.
// R:passagem de valor: copia. passagem por referência: &. não quero dar exemplo não

// 6) Implemente uma função que receba dois inteiros e troque seus valores usando ponteiros.
// R:
// void troca(int *x, int *y){
//     int nig = *y;
//     *y = *x;
//     *x = nig;
// }
// int main(){
//     int a = 20, b = 30;
//     printf("%i, %i", a, b);
//     troca(&a, &b);
//     printf("\n%i, %i", a, b);
// }

// 📌 4. Vetores e Strings
// 7) Dado: int v[5] = {1,2,3,4,5};
// a) Qual o valor de v[2]? b) Qual a diferença entre v e &v[0]?
// R: v[2] = 3. v = ponteiro, v[0] = 1
// 8) Escreva uma função que: receba um vetor de inteiros e retorne a soma de seus elementos.
// R:
// int soma(int nig[], int tam){
//     int resultado = 0;
//     for(int i = 0; i < tam; i++){
//         resultado += nig[i];
//     }
//     return resultado;
// }

// int main(){
//     int ni[5] = {1,3,4,5,8};
//     printf("%d", soma(ni,5));
// }

// 9) Dado: char nome[] = "UFFS";
// a) Quantos caracteres existem na string?
// R: 5
// b) Qual é o caractere final invisível?
// R:'\0'
// c) Por que ele é importante?
// R: Para encerrar a string

// 📌 5. Matrizes
// 10) Escreva um programa que: leia uma matriz 2x2, calcule e mostre o determinante.
// 11) Faça uma função que receba uma matriz 3x3 e imprima sua transposta.

// 📌 6. Structs
// 12) Dada a struct: typedef struct { int x; int y; } Ponto;
// a) Crie uma função que inicialize um ponto. b) Crie uma função que calcule a distância entre dois pontos.
// R:
// #include <stdio.h>
// #include <math.h>
// typedef struct
// {
//     int x;
//     int y;
// } Ponto;
// Ponto setpoint(int a, int b){
//     Ponto p;
//     p.x = a;
//     p.y = b;
//     return p;
// }
// double distpoint(Ponto A, Ponto B){
//     int rx, ry;
//     rx = B.x - A.x;
//     ry = B.y - A.y;
//     return sqrt((rx *rx) + (ry * ry));
// }
// int main(){
//     printf("%i",distpoint(setpoint(4,5), setpoint(6,9)));
// }

// 📌 7. TAD (Tipo Abstrato de Dados)
// 13) Explique o conceito de TAD.
// Deixar separado a função do código da chamada, da para esconder as funções de código
// 14) Implemente um TAD simples para um “Retângulo” com: largura, altura.
// Funções: criar, calcular área, calcular perímetro.
// R:
// rectangle.h
// typedef struct{
//     int altura, largura;
// } retangulo;

// retangulo setrectangle(int, int);

// int calArea(retangulo);

// int calPerimeter(retangulo);

// rectangle.c
// #include <stdio.h>
// #include "rectangle.h"

// retangulo setrectangle(int a, int l){
//     retangulo R;
//     R.altura = a;
//     R.largura = l;
//     return R;
// }

// int calArea(retangulo R){
//     int resultado = R.altura * R.largura;
//     return resultado;
// }

// int calPerimeter(retangulo R){
//     return 2 * (R.altura + R.largura);
// }

// cliente.c
// #include <stdio.h>
// #include "rectangle.h"

// int main(){
//     printf("%d", calArea(setrectangle(4,5)));
//     printf("\n%d", calPerimeter(setrectangle(4,5)));
// }

// 📌 8. Recursividade
// 15) O que é uma função recursiva? Explique o conceito de caso base.
// 16) Analise:
// int f(int n){
//  if (n == 0) return 0;
//  return n + f(n-1);
//}
// a) O que essa função faz?
// R: ela soma todos os números atrás
// b) Qual o resultado de f(4)?
// R: 4+3+2+1+0
// 17) Escreva uma função recursiva que calcule o fatorial de um número.
// #include <stdio.h>
// int fatorial(int n){
//     if(n == 1) return 1;
//     return n * fatorial(n - 1);
// }

// int main(){
//     printf("%d", fatorial(4));
//     return 0;
// }

// 18) Escreva uma função recursiva que conte quantas vezes um número pode ser dividido por 2 até chegar a 1.
// R:
// #include <stdio.h>

// int div(int n){
//     if(n <= 1) return 0;
//     return 1 + div(n/2);
// }
// int main(){
//     printf("%i", div(32));
// }

// 🔥 Questão estilo PROVA COMPLETA (mais difícil)
// 19) Implemente um programa que: Crie uma struct Aluno com nome (string) e nota (float).
// Crie um vetor de 5 alunos. Faça funções para: cadastrar alunos, mostrar alunos, calcular média das notas.
// Use ponteiros para manipular os dados.
#include <stdio.h>
#include <string.h>

typedef struct
{
    char nome[30];
    double nota;
} aluno;

void setaluno(aluno *, int);

void showaluno(aluno *, int);

double medianota(aluno *, int);

int main()
{
    aluno turma[5];
    setaluno(turma, 5);

    printf("\n");

    showaluno(turma, 5);

    printf("\n Média: %d", medianota(turma, 5));

    return 0;
}

void setaluno(aluno *a, int n)
{
    for (int i = 0; i < n; i++)
    {
        printf("Nome: ");
        scanf("%s", a[i].nome);
        printf("Nota: ");
        scanf("%d", &a[i].nota);
    }
}

void showaluno(aluno *a, int t)
{
    for (int i = 0; i < t; i++)
    {
        printf("Aluno: %s \nNota: %d\n", a[i].nome, a[i].nota);
    }
}

double medianota(aluno *a, int t)
{
    double acumula = 0;
    for (int i = 0; i < t; i++)
    {
        acumula += a[i].nota;
    }
    return acumula / t;
}