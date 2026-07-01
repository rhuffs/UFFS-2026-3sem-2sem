#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
    printf("====== Cadastro =======\n");
    printf("| 1. Livros            |\n");
    printf("| 2. Usuários          |\n");
    printf("| 0. Voltar            |\n");
    printf("=======================\n");
}

void menuConsulta(){
    printf("======= Consulta =======\n");
    printf("| 1. Livros            |\n");
    printf("| 2. Usuários          |\n");
    printf("| 3. Empréstimos       |\n");
    printf("| 0. Voltar            |\n");
    printf("=======================\n");
}

void menuAtualizacao(){
    printf("======= Atualizar ======\n");
    printf("| 1. Livros            |\n");
    printf("| 2. Usuários          |\n");
    printf("| 0. Voltar            |\n");
    printf("=======================\n");
}

void menuExclusao(){
    printf("======== Excluir =======\n");
    printf("| 1. Livros            |\n");
    printf("| 2. Usuários          |\n");
    printf("| 0. Voltar            |\n");
    printf("=======================\n");
}

int main() {
    Users *lista = NULL;
    int op;
    int opCad;
    int opExcluir;
    int opAtu;
    int opConsul;

    do {
        menuPrincipal();
        printf("Escolha uma opção: ");
        op = lerInteiro("Escolha uma opção: ");

        switch (op) {
            case 1:
                
                do{
                    menuCadastro();
                    opCad = lerInteiro("Escolha uma opção: ");
                    switch (opCad){
                    case 1:
                        cadastrarLivro();
                        break;

                    case 2: {

                        char nome[100];
                        char email[100];

                        printf("Digite o nome do usuario: ");
                        scanf(" %99[^\n]", nome);//lê uma linha inteira, incluindo espaços

                        printf("Digite o email do usuario: ");
                        scanf(" %99[^\n]", email);

                        lista = CadastrarUsuarios(lista, nome, email);

                        break;
                    } 
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
                do{
                    menuConsulta();
                    opConsul = lerInteiro("Escolha uma opção: ");
                    switch (opConsul){
                    case 1:
                        consultarLivro();
                        break;

                    case 2 : {
                        char email[100];
                        printf("Digite o email do usuario: ");
                        scanf(" %99[^\n]", email);

                        Users *usuario = consultaUser(lista, email);

                        if (usuario == NULL) {
                            printf("Usuario nao encontrado.\n");
                        } else {
                            printf("\nUsuario encontrado!\n");
                            printf("Nome : %s\n", usuario->nome);
                            printf("Email: %s\n", usuario->email);
                        }

                        break;
                    }
                    case 3: {
                        char email[100];
                        printf("Digite o email do usuario: ");
                        scanf(" %99[^\n]", email);
                        listarEmprestimos(raizeslivros, email);
                        break;
                    }
                    case 0:
                        printf("0: Voltar\n");
                        break;
                    
                    default:
                        printf("Opção inválida\n");
                        break;
                    }

                }while(opConsul !=0);
                break;

            case 3:
                do{
                    menuAtualizacao();
                    opAtu = lerInteiro("Escolha uma opção: ");
                    switch (opAtu){
                    case 1:
                        updatebook(); 
                        break;

                    case 2: {
                        char email[100];
                        printf("Digite o email do usuario: ");
                        scanf("%99[^\n]", email);
                        atualizaUsuarios(lista, email);
                        break;
                    }
                    case 0:
                        printf("0: Voltar\n");
                        break;
                    
                    default:
                        printf("Opção inválida\n");
                        break;
                    }

                }while(opAtu !=0);
                break;

            case 4:
                do{
                    menuExclusao();
                    opExcluir = lerInteiro("Escolha uma opção: ");
                    switch (opExcluir){
                    case 1:
                        deleteBook();
                        break;

                    case 2: {
                        char email[100];
                        printf("Digite o email do usuario: ");
                        scanf("%99[^\n]", email);
                        lista = excluirUsuario(lista, email);
                        break;
                    }
                    case 0:
                        printf("0: Voltar\n");
                        break;
                    
                    default:
                        printf("Opção inválida\n");
                        break;
                    }

                }while(opExcluir !=0);
                break;

            case 5:
                loanBook();
                break;

            case 6:
                devolverLivro();
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