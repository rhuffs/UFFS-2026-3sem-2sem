#include <stdio.h>
#include <math.h>

// --- ESTRUTURAS ---
typedef struct
{
    int x;
    int y;
} Ponto;

typedef struct
{
    int altura, largura;
} retangulo;

typedef struct
{
    char nome[30];
    double nota;
} aluno;

// --- FUNÇÕES ---

// 1. Altera valor via ponteiro
void altera(int *x)
{
    *x = 50;
}

// 2. Troca valores entre duas variáveis
void troca(int *x, int *y)
{
    int nig = *y;
    *y = *x;
    *x = nig;
}

// 3. Soma elementos de um array
int soma(int nig[], int tam)
{
    int resultado = 0;
    for (int i = 0; i < tam; i++)
    {
        resultado += nig[i];
    }
    return resultado;
}

// 4. Funções de Ponto
Ponto setpoint(int a, int b)
{
    Ponto p;
    p.x = a;
    p.y = b;
    return p;
}

double distpoint(Ponto A, Ponto B)
{
    int rx = B.x - A.x;
    int ry = B.y - A.y;
    return sqrt((rx * rx) + (ry * ry));
}

// 5. Funções de Retângulo
retangulo setrectangle(int a, int l)
{
    retangulo R;
    R.altura = a;
    R.largura = l;
    return R;
}

int calArea(retangulo R)
{
    return R.altura * R.largura;
}

int calPerimeter(retangulo R)
{
    return 2 * (R.altura + R.largura);
}

// 6. Fatorial Recursivo
int fatorial(int n)
{
    if (n <= 1)
        return 1;
    return n * fatorial(n - 1);
}

// 7. Divisão Recursiva (Log2)
int div_recursiva(int n)
{
    if (n <= 1)
        return 0;
    return 1 + div_recursiva(n / 2);
}

// Turma com alunos
void setaluno(aluno *, int);
void showaluno(aluno *, int);
double medianota(aluno *, int);

// --- MAIN ÚNICA ---
int main()
{
    // Teste Altera
    int a_alt = 10;
    altera(&a_alt);
    printf("Altera: %d\n", a_alt);

    // Teste Troca
    int a_tr = 20, b_tr = 30;
    troca(&a_tr, &b_tr);
    printf("Troca: %d, %d\n", a_tr, b_tr);

    // Teste Soma Array
    int ni[5] = {1, 3, 4, 5, 8};
    printf("Soma Array: %d\n", soma(ni, 5));

    // Teste Ponto (Distância)
    printf("Distancia Pontos: %.2f\n", distpoint(setpoint(4, 5), setpoint(6, 9)));

    // Teste Retângulo
    retangulo meuRet = setrectangle(4, 5);
    printf("Area Ret: %d, Perimetro Ret: %d\n", calArea(meuRet), calPerimeter(meuRet));

    // Teste Fatorial
    printf("Fatorial (4): %d\n", fatorial(4));

    // Teste Divisão (Log2)
    printf("Divisoes de 32: %d\n", div_recursiva(32));

    aluno turma[5];

    setaluno(turma, 5);
    printf("\n");

    showaluno(turma, 5);

    printf("\nMedia: %.2f\n", medianota(turma, 5));


    return 0;
}


void setaluno(aluno *a, int n){
    for(int i = 0; i < n; i++){
        printf("Nome: ");
        scanf("%s", a[i].nome);

        printf("Nota: ");
        scanf("%lf", &a[i].nota);
    }
}

void showaluno(aluno *a, int t){
    for(int i = 0; i < t; i++){
        printf("Aluno: %s\nNota: %.2f\n", a[i].nome, a[i].nota);
    }
}

double medianota(aluno *a, int t){
    double acumula = 0;

    for(int i = 0; i < t; i++){
        acumula += a[i].nota;
    }

    return acumula / t;
}