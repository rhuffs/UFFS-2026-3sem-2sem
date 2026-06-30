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

void consultarEmprestimos() {
    char email[100];
    
    printf("\n--- CONSULTAR EMPRÉSTIMOS ---\n");
    lerString(email, 100, "Digite o email do usuário: ");
    
    printf("\n--- Livros emprestados para %s ---\n", email);
    
    if (raizeslivros == NULL) {
        printf("Nenhum livro cadastrado.\n");
        return;
    }
    
    // Percorre a árvore de livros (usando pilha)
    NoBooks *pilha[1000];
    int topo = -1;
    NoBooks *atual = raizeslivros;
    int encontrou = 0;
    
    while (atual != NULL || topo >= 0) {
        while (atual != NULL) {
            pilha[++topo] = atual;
            atual = atual->esq;
        }
        atual = pilha[topo--];
        if (atual->Livro->status == 1 && 
            strcmp(atual->Livro->Emprestadoemail, email) == 0) {
            printf("ID: %d | Título: %s | Autor: %s\n",
                   atual->Livro->id, atual->Livro->titulo, atual->Livro->autor);
            encontrou = 1;
        }
        atual = atual->dir;
    }
    
    if (!encontrou) {
        printf("Este usuário não possui livros emprestados.\n");
    }
}

int main() {

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
                    printf("Escolha uma opção: ");
                    opCad = lerInteiro("Escolha uma opção: ");
                    switch (opCad){
                    case 1:
                        cadastrarLivro();
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
                do{
                    menuConsulta();
                    printf("Escolha uma opção: ");
                    opConsul = lerInteiro("Escolha uma opção: ");
                    switch (opConsul){
                    case 1:
                        consultarLivro();
                        break;

                    case 2:
                        printf("2: Usuarios\n");
                        break;

                    case 3:
                        printf("0: Empréstimos\n");
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

            case 3:
                do{
                    menuAtualizacao();
                    printf("Escolha uma opção: ");
                    opAtu = lerInteiro("Escolha uma opção: ");
                    switch (opAtu){
                    case 1:
                        updatebook(); 
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

            case 4:
                do{
                    menuExclusao();
                    printf("Escolha uma opção: ");
                    opExcluir = lerInteiro("Escolha uma opção: ");
                    switch (opExcluir){
                    case 1:
                        deleteBook();
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