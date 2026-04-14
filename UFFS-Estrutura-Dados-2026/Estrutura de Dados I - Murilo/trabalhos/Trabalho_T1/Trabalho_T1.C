#include<stdio.h>



int main(){
    int ESCOLHA;
    printf("Escolha qual questao ira querer: ");
    scanf("%i", &ESCOLHA);

    //QUESTÃO 1
    if(ESCOLHA == 1){
        int horas, valorH, salario;

        printf("Horas trabalhadas: ");
        scanf("%i", &horas);
        printf("Valor por Horas trabalhadas: ");
        scanf("%i", &valorH);

        if (horas > 200){
            salario = horas *valorH;
            int acrescimo = salario * 0.05;
            salario += acrescimo;
            
        }
        else{
            salario = horas *valorH;
        }

        printf("Resultado do seu salario: %i", salario);
    }

    //QUESTÃO 2
    else if (ESCOLHA == 2){
        int PreProduto, FPagamento;

        printf("Preco do produto: ");
        scanf("%i", &PreProduto);
        printf("Forma de Pagamento: \n 1 para a vista\n2 para a prazo: \n");
        scanf("%i", &FPagamento);

        if(FPagamento == 1){
            int desconto = PreProduto * 0.05;
            PreProduto -= desconto;        
        }
        else{
            int acrescimo = PreProduto * 0.10;
            PreProduto += acrescimo;
        }
        printf("%i", PreProduto);
    }

    //QUESTÃO 3
    else if (ESCOLHA == 3){
        int inicio, fim, resultado;

        printf("Inicio: ");
        scanf("%i", &inicio);
        printf("Fim: ");
        scanf("%i", &fim);
        

        if(inicio > fim){
            resultado = (24 - inicio) + fim;
        }
        
        else if(inicio < fim){
            resultado = inicio - fim;
        }

        else{
            resultado = 24;
        }

        printf("%i Horas de duracao", resultado);
    }

    //QUESTÃO 4
    else if(ESCOLHA == 4){
        int num, neg = 0,pos = 0;

        for(int i = 1; i < 5; i++ ){
            printf("N%i:", i);
            scanf("%i", &num);

            if(num <0){
                neg++;
            }
            else{
                pos++;
            }            
        }
        printf("%i (+) e %i (-)", neg, pos);
    }

    //QUESTÃO 5
    else if (ESCOLHA == 5){
        int num1, num2, somador = 0;

        printf("Multiplicador: ");
        scanf("%i", &num1);
        printf("Multiplicado: ");
        scanf("%i", &num2);
        
        for(int i = 0; i < num2; i++){
            somador += num1;
        }
        printf("Resultado: %i", somador);
    }

    //QUESTÃO 6
    else if(ESCOLHA == 6){
        int alcance , soma = 0;

        printf("N: ");
        scanf("%i", &alcance);

        for (int i = 1; i < alcance + 1; i++){
            soma += i;
        }

        printf("Resultado: %i", soma);
    }

    //QUESTÃO 7
    else if(ESCOLHA == 7){
        int numero = 1, contador = 0, total = 0;
        float resultado;

        while (numero > 0){
            total ++;

            printf("Numero (menor ou igual a 0 para sair): ");
            scanf("%i", &numero);

            if (numero >= 10 && numero <= 20){
                contador ++;
            }
        }

        resultado = ((float)contador/ total) * 100;
        printf("Resultado: %.2f", resultado);
    }
    //QUESTÃO 8
    else if(ESCOLHA == 8){
        int filhos = 0, total = 0, totalF = 0;
        float salario, mediaF, mediaS, totalS = 0;

        while(salario >= 0){
            printf("Salario (menor que 0 para sair): ");
            scanf("%f", &salario);
            
            if(salario < 0) break;


            
            printf("Filhos: ");
            scanf("%i", &filhos);

            totalF += filhos;
            totalS += salario;
            total ++;
        }

        mediaF = (float)totalF/total;
        mediaS = totalS/total;
        printf("%.2f Media salarial\n%.2f Media dos filhos", mediaS, mediaF);
    }

    //QUESTÃO 9
    else if(ESCOLHA == 9){
        int matricula = 1, total = 0, totalTurma = 0;
        float nota = 0, mediaAluno = 0, acumuloAluno = 0, mediaTurma = 0, acumuloTurma = 0;

        while(matricula >= 0){
            printf("Matricula (0 para sair): ");
            scanf("%i", &matricula);

            if(matricula < 1) break;

            acumuloAluno = 0;
                        
            for(int i = 1; i <=5 ; i++){
                printf("Nota %i: ",i);
                scanf("%f", &nota);

                acumuloAluno += nota;
                total ++;
            }

            mediaAluno = acumuloAluno/5;
            printf("Aluno: %i \nMedia: %.2f\n", matricula, mediaAluno);
            acumuloTurma += mediaAluno;
            totalTurma ++;
        }

        mediaTurma = acumuloTurma/totalTurma;
        printf("Media da turma: %.2f", mediaTurma);
    }

    //QUESTÃO 10
    else if(ESCOLHA == 10){
        int numero, resultado = 1;
        printf("Numero: ");
        scanf("%i", &numero);
        for(int i = numero; i > 1; i--){
            resultado *= i;
        }

        printf("Resultado: %i", resultado);
    }
}