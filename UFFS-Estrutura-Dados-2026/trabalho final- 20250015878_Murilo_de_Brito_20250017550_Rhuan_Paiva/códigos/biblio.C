#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "biblio.h"

//Raízes
NoBooks *raizeslivros = NULL;
//alocar o Livro
NoBooks *NoPlivro(Books *L){
    NoBooks *newL = (NoBooks *)malloc(sizeof(NoBooks));
    newL->Livro = L;
    newL->dir = NULL;
    newL->esq = NULL;
    return newL;
}

//inserir novo livro
NoBooks *InsertNewBook(NoBooks *raizL, Books *Livro){
    NoBooks *NewL = NoPlivro(Livro);
    if(raizL == NULL) return NewL;
    else{
        NoBooks *aux = raizL;
        NoBooks *pai = NULL;
        while(aux != NULL){
            pai = aux;
            if(aux->Livro->id > Livro->id) aux = aux->esq;
            else if(aux->Livro->id < Livro->id) aux = aux->dir;
            else{
                printf("!!ERROR!!\n>ID(%d) do livro já existe", Livro->id);
                free(Livro);
                free(NewL);
                return raizL;
            }
        }
        if(pai->Livro->id > Livro->id) pai->esq = NewL;
        else pai->dir = NewL;
        return raizL;
    }
}

Books *findBook(NoBooks *raiz, int id){
    NoBooks *aux = raiz;
    while(aux != NULL){
        if(id == aux->Livro->id) return aux->Livro;
        else if(aux->Livro->id > id) aux = aux->esq;
        else aux = aux->dir;
    }
    return;
}

// Encontrar extremo (mínimo ou máximo)
NoBooks *ExtremeBook(NoBooks *raizL, int buscarMinimo) {
    if (raizL == NULL) return NULL;
    NoBooks *aux = raizL;
    if (buscarMinimo)  while (aux->esq != NULL) aux = aux->esq;
    else while (aux->dir != NULL) aux = aux->dir;
    return aux;
}

// Gerar próximo ID automaticamente
int nextIDbook(NoBooks *raizL) {
    if (raizL == NULL) return 1;//1 = mínimo
    NoBooks *maior = ExtremeBook(raizL, 0);  // 0 = máximo
    return maior->Livro->id + 1;
}

//remover os Livros
NoBooks *removeBook(NoBooks *raiz, int id) {
    if (raiz == NULL) {
        printf("!!ERROR!!\n>Livro com ID (%d) não encontrado.\n", id);
        return NULL;
    }

    if (id < raiz->Livro->id) raiz->esq = removeBook(raiz->esq, id);
     else if (id > raiz->Livro->id) raiz->dir = removeBook(raiz->dir, id);
     else {
        if (raiz->esq == NULL) {
            NoBooks *aux = raiz->dir;
            free(raiz->Livro);  
            free(raiz);         
            return aux;
        }
        if (raiz->dir == NULL) {
            NoBooks *aux = raiz->esq;
            free(raiz->Livro);  
            free(raiz);         
            return aux;
        }
        
        NoBooks *aux = raiz->dir;
        while (aux->esq != NULL) {
            aux = aux->esq;
        }
        
        Books *livroTemp = raiz->Livro;
        raiz->Livro = aux->Livro;
        aux->Livro = livroTemp;
        
        raiz->dir = removeBook(raiz->dir, aux->Livro->id);
    }
    
    return raiz;
}

//listar os livros->in order
void ListBooks(NoBooks *RaizL){
    if(RaizL == NULL) return;
    ListBooks(RaizL->esq);
    printf("|ID: %d | título: %s | autor: %s | ano: %d | status : %s|", RaizL->Livro->id, RaizL->Livro->titulo, RaizL->Livro->autor, RaizL->Livro->ano, (RaizL->Livro->status == 0 ) ? "Disponível" : "Emprestado");
    if(RaizL->Livro->status == 1) printf("> Usuário com o livro: %s", RaizL->Livro->Emprestadoemail);
    ListBooks(RaizL->dir);
}

//listar os livros de um autor específico
void ListBooksperAuthor(NoBooks *Raizl, char *autor){
    if(Raizl == NULL) return;
    ListBooks(Raizl->esq);
    if(strcmp(Raizl->Livro->autor, autor) == 0){//se for igual
        printf("|ID: %d | título: %s | ano: %d | status : %s|", Raizl->Livro->id, Raizl->Livro->titulo, Raizl->Livro->ano, (Raizl->Livro->status == 0 ) ? "Disponível" : "Emprestado");
    }
    ListBooksperAuthor(Raizl, autor);
}

void ReleaseBook(NoBooks *RaizL){
    if(RaizL == NULL) return;
    ReleaseBook(RaizL->esq);
    ReleaseBook(RaizL->dir);
    free(RaizL->Livro);
    free(RaizL);
}

void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {}
}

// Ler uma string (texto) do usuário de forma segura
//ela resolve junto com o limparBuffer, o problema do buffer de entrada
int lerString(char *destino, int tamanho, char *mensagem) {
    printf("%s", mensagem);
    if (fgets(destino, tamanho, stdin) != NULL) {
        int TAM = strlen(destino);
        if (TAM > 0 && destino[TAM-1] == '\n') {
            destino[TAM-1] = '\0'; // Remove o [ENTER] do final
        } else {
            limparBuffer();
        }
        return 1;
    }
    return 0;
}

int lerInteiro(char *mensagem) {
    char Tempchar[20];
    int valor;
    while (1) {
        printf("%s", mensagem);
        if (fgets(Tempchar, sizeof(Tempchar), stdin) != NULL) {
            int tam = strlen(Tempchar);
            if (tam > 0 && Tempchar[tam-1] == '\n') Tempchar[tam-1] = '\0';
            else limparBuffer();
            if (sscanf(Tempchar, "%d", &valor) == 1) {
                return valor;
            }
        }
        printf("Entrada inválida. Digite um número inteiro.\n");
    }
}

//registrar o livro
void cadastrarLivro(){
    Books *NewL = (Books *)malloc(sizeof(Books));
    NewL->id = nextIDbook(raizeslivros);

    printf("\n> CADASTRO DE LIVRO\n");
    printf("> ID gerado para o \n  livro automaticamente: %d\n", NewL->id);
    lerString(NewL->titulo, 100, "Título: ");
    lerString(NewL->autor, 100, "Autor: ");
    NewL->ano = lerInteiro("Ano de publicação: ");
    NewL->status = 0;
    NewL->Emprestadoemail[0] = '\0';
    raizeslivros = InsertNewBook(raizeslivros, NewL);
    printf("> LIVRO CADASTRADO ");
}

//consultar livro
void consultarLivro(){
    int opcao;
    printf("\n> CONSULTA DE LIVROS:\n");
    printf("|     por código (ID)    |\n");
    printf("|        por autor       |\n");
    printf("| Listar todos os livros |\n");
    opcao = lerInteiro("Opção: ");
    //por livro com ID
    if(opcao == 1){
        int id = lerInteiro("Digite o id do livro: ");
        Books *acharlivro = findBook(raizeslivros, id);
        if(acharlivro != NULL){
            printf("\n> DADOS DO LIVRO: \n|   ID:  %d | \n|título: %s | \n| autor: %s |\n|  ano:  %d |\n |status : %s|", acharlivro->id, acharlivro->titulo, acharlivro->autor, acharlivro->ano, (acharlivro->status == 0 ) ? "Disponível" : "Emprestado");
        }
        else printf("Livro não encontrado");
    }
    //livros por autor
    if(opcao == 2){
        char autor[100];
        lerString(autor, 100, "Digite o nome do autor");
        printf("\n> Livros de Sr.(a) %s", autor);
        ListBooksperAuthor(raizeslivros, autor);
    }
    if(opcao == 3){
        if(raizeslivros == NULL) printf(">Nenhum livro encontrado\n");
        else {
            printf("> lista de todos os livros\n");
            ListBooks(raizeslivros);
        }
    }
    else printf("Operação inválida");
}

//void atualizar o livro
void devolverLivro(){
    int id = lerInteiro("Digite o ID do livro: ");
    Books *livro = findBook(raizeslivros, id);
    if(livro == NULL) printf("arquivo não encontrado"); return;
    if(livro->status == 0) {
        printf("O livro (%s) não está emprestado", livro->titulo); 
        return;
    }
    printf("Devolução do livro %s, emprestado do usuario %s", livro->titulo, livro->Emprestadoemail);
    livro->status = 0;
    livro->Emprestadoemail[0] = '\0';
    printf("livro devolvido com sucesso");

}

void deleteBook(){
    int id = lerInteiro("Digite o ID do livro para remoção: ");
    Books *livro = findBook(raizeslivros, id);
    if(livro == NULL) {
        printf("arquivo não encontrado"); 
        return;
    }
    if(livro->status == 1) {
        printf("   !!ERROR!!\n O livro (%s) está sendo emprestado por: %s", livro->titulo, livro->Emprestadoemail); 
        return;
    }
    printf("Tem certeza que deseja excluir o livro %s?\n> (1-Sim / 0-Não): ", livro->titulo);
    int confirm = lerInteiro("");
    if(confirm == 1) {
        raizeslivros = removeBook(raizeslivros, id); 
        printf("Arquivo deletado com sucesso");
    }
    else{
        printf("operação cancelada\n");
        return;
    }
}

void loanBook(){
    int id = lerInteiro("Digite o ID do livro que queira ser emprestado: ");
    Books *livro = findBook(raizeslivros, id);
    if(livro == NULL) {
        printf("arquivo não encontrado"); 
        return;
    }
    if(livro->status == 1) {
        printf("O livro da ID %d '%s' já está sendo utilizado por: %s\n",livro->id, livro->titulo, livro->Emprestadoemail); 
        return;
    }
    if (livro->status == 1) {
        printf("Livro já está emprestado para %s.\n", livro->Emprestadoemail);
        return;
    }
    char insertemail[100];
    lerString(insertemail, 100, "Digite o seu e-mail: ");
        livro->status = 1;
    strcpy(livro->Emprestadoemail, insertemail);
    
    printf("✓ Empréstimo realizado com sucesso!\n");
    printf("  Livro: %s\n", livro->titulo);
    printf("  Usuário: %s\n", insertemail);
}

void updatebook(){
        int id = lerInteiro("Digite o ID do livro que queira ser emprestado: ");
    Books *livro = findBook(raizeslivros, id);
    if(livro == NULL) {
        printf("arquivo não encontrado"); 
        return;
    }
    printf("\n> ATUALIZANDO LIVRO ID %d \n", id);
    printf("| Título atual: %s |\n", livro->titulo);
    printf("| Autor atual: %s  |\n", livro->autor);
    printf("|   Ano atual: %d  |\n", livro->ano);

    printf("\n> O que deseja alterar?\n");
    printf("| 1. Título |\n");
    printf("|  2. Autor |\n");
    printf("|   3. Ano  |\n");
    int opcao = lerInteiro("Opção: ");

        switch(opcao) {
        case 1:
            lerString(livro->titulo, 100, "Novo título: ");
            printf("\n> Título atualizado com sucesso!\n");
            break;
        case 2:
            lerString(livro->autor, 100, "Novo autor: ");
            printf("\n> Autor atualizado com sucesso!\n");
            break;
        case 3:
            livro->ano = lerInteiro("Novo ano: ");
            printf("\n> Ano atualizado com sucesso!\n");
            break;
        default:
            printf("Opção inválida!\n");
    }
}
