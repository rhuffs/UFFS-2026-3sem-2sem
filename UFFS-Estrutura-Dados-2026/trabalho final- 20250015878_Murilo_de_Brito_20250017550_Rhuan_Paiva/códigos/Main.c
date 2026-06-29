#include <stdio.h>
#include <stdlib.h>
#include "biblio.h"

void menuPrincipal() {
    printf("========= Menu =========\n");
    printf("| 1. Cadastro          |\n");
    printf("| 2. Consulta          |\n");
    printf("| 3. Atualização       |\n");
    printf("| 4. Exclusão          |\n");
    printf("| 5. Empréstimo        |\n");
    printf("| 6. Devolução         |\n");
    printf("| 0. Sair              |\n");
    printf("=========================\n");
}

void menuCadastro(){
    printf("========= Menu ========\n");
    printf("| 1. Livros            |\n");
    printf("| 2. Usuários          |\n");
    printf("| 0. Voltar            |\n");
    printf("=======================\n");
}

int main() {

    int op;
    int opCad;

    do {
        menuPrincipal();
        printf("Escolha uma opção: ");
        scanf("%d", &op);

        switch (op) {
            case 1:
                
                do{
                    menuCadastro();
                    printf("Escolha uma opção: ");
                    scanf("%d", &opCad);
                    switch (opCad){
                    case 1:
                        printf("1: Livros\n");
                        break;

                    case 2:
                        printf("2: Usuarios\n");
                        break;

                    case 0:
                        printf("0: Voltar\n");
                        break;
                    
                    default:
                        printf("Opção inválida\n");
                        break;
                    }

                }while(opCad !=0);
                break;

            case 2:
                printf("Consulta\n");
                break;

            case 3:
                printf("Atualização\n");
                break;

            case 4:
                printf("Exclusão\n");
                break;

            case 5:
                printf("Empréstimo\n");
                break;

            case 6:
                printf("Devolução\n");
                break;

            case 0:
                printf("Saindo...\n");
                break;

            default:
                printf("Opção inválida!\n");
        }

    } while (op != 0);

    return 0;
}