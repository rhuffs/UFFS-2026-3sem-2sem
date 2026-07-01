#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "biblio.h"


Users *CadastrarUsuarios(Users *lista,char *nome, char *email){
    Users *novo = (Users *)malloc(sizeof(Users));
    if (novo == NULL) {
        printf("Erro ao alocar memória\n");
        return lista;
    }
    strcpy(novo->nome, nome);
    strcpy(novo->email, email);
    novo->next = NULL;
    

    Users *aux = lista;
    if (lista == NULL){
        return novo;
    }

    while (aux != NULL){

        if(strcmp(aux->email, email) == 0){
            printf("Email já cadastrado\n");
            free(novo);
            return lista;
        }

        if(aux->next == NULL)
            break;

        aux = aux->next;
    }

    aux->next = novo;

    return lista;
}

Users *consultaUser(Users *lista, char *email){
    Users *aux = lista;
    
    while (aux != NULL){
        if (strcmp(aux->email,email)==0){
            return aux;
        }

        aux = aux->next;
    }

    return NULL;
}

void listarEmprestimos(NoBooks *raiz, char *email){
    if(raiz == NULL){
        return;
    }
    listarEmprestimos(raiz->esq, email);

    if(strcmp(raiz->Livro->Emprestadoemail, email) == 0){

        printf("ID: %d\n", raiz->Livro->id);
        printf("Titulo: %s\n", raiz->Livro->titulo);
        printf("Autor: %s\n", raiz->Livro->autor);
        printf("Ano: %d\n\n", raiz->Livro->ano);

    }

    listarEmprestimos(raiz->dir, email);
}


void atualizaUsuarios(Users *lista, char email[]){
    Users *usuario = consultaUser(lista, email);
    if (usuario == NULL){
        printf("Usuario não encontrado.\n");
        return;
    }
    printf("Digite o novo nome: ");
    scanf(" %99[^\n]", usuario->nome); //Lê a linha inteira, inclusive espaços.O espaço antes do % faz o scanf ignorar o '\n' que ficou no buffer.99 evita escrever além do tamanho do vetor.
}

Users *excluirUsuario(Users *lista, char email[]) {

    Users *atual = lista;
    Users *anterior = NULL;

    while (atual != NULL && strcmp(atual->email, email) != 0) {
        anterior = atual;
        atual = atual->next;
    }

    if (atual == NULL) {
        printf("Usuario nao encontrado.\n");
        return lista;
    }

    if (anterior == NULL) {
        lista = atual->next;
    } else {
        anterior->next = atual->next;
    }
    free(atual);
    printf("Usuario removido com sucesso!\n");
    return lista;
}