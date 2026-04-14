#include<stdio.h>

int main (){

    int Matricula = 1; 
    float nota;
    int i;
    float MediaAluno = 0;
    float MediaTurma = 0;
    float MediaAluno2 = 0;
    int Turma = 0;
    float SomaMedia = 0 ;
    while (1)
    {   
       
        printf("Digite a matricula :");
        scanf("%d", &Matricula);
        if (Matricula == 0){
            break;
        }
        

        Turma ++;
        for(i = 0; i < 5; i ++){
            
            printf("Digite a nota :");
            scanf("%f", &nota);
            MediaAluno = MediaAluno + nota;
                
        }
        
        MediaAluno2 = MediaAluno / 5;
        SomaMedia = SomaMedia + MediaAluno2; 
        printf("Media do aluno:%.2f", MediaAluno2);
        MediaAluno = 0;

    }

    MediaTurma = SomaMedia / Turma;
    printf("A Media da sala é: %.2f", MediaTurma); 
    
}