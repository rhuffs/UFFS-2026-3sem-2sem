#include <stdio.h>

int main()
{
    int matricula = 1, total = 0, totalTurma = 0;
    float nota = 0, mediaAluno = 0, acumuloAluno = 0, mediaTurma = 0, acumuloTurma = 0;

    while (matricula > 0)
    {
        printf("Matricula (0 para sair): ");
        scanf("%i", &matricula);

        if (matricula < 1)
            break;

        acumuloAluno = 0;

        for (int i = 1; i <= 5; i++)
        {
            printf("Nota %i: ", i);
            scanf("%f", &nota);

            acumuloAluno += nota;
            total++;
        }

        mediaAluno = acumuloAluno / 5;
        printf("Aluno: %i \nMedia: %.2f\n", matricula, mediaAluno);
        acumuloTurma += mediaAluno;
        totalTurma++;
        printf("Matricula (0 para sair): ");
        scanf("%i", &matricula);
    }

    mediaTurma = acumuloTurma / totalTurma;
    printf("Media da turma: %.2f", mediaTurma);
    return 0;
}