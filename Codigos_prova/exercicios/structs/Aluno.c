#include <stdio.h>
#include <string.h>

typedef struct {
    char nome[30];
    float nota;
} aluno;

aluno cadasAluno(char *i, float n){
    aluno a;

    strcpy(a.nome, i);
    a.nota = n;

    return a;

}

void mostrarAlunos(aluno v[], int qtd){
    for(int i = 0; i < qtd; i++){
        printf("Aluno %d:\n", i + 1);
        printf("Nome: %s\n", v[i].nome);
        printf("Nota: %.2f\n", v[i].nota);
        printf("\n");
    }
}

float calcularMedia(aluno v[], int qtd){
    if(qtd == 0) return 0;

    float soma = 0;

    for(int i = 0; i < qtd; i++){
        soma += v[i].nota;
    }

    return soma / qtd;
}

int main(){
    aluno turma[5];

    turma[0] = cadasAluno("Ana", 8.5);
    turma[1] = cadasAluno("Bruno", 7.0);
    turma[2] = cadasAluno("Carlos", 9.2);

    mostrarAlunos(turma, 3);

    printf("Media: %.2f\n", calcularMedia(turma, 3));
}