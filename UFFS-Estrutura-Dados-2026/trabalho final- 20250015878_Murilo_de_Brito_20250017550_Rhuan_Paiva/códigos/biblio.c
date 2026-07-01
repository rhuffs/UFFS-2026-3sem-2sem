#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "biblio.h"


//alocar o Livro
NoBooks *NoPlivro(Books *L){
    NoBooks *newL = (NoBooks *)malloc(sizeof(NoBooks));
    if(!newL) return NULL;
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
    return NULL;
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
    int id;
    do {
        id = rand() % 1000000 + 1;  // ID entre 1 e 1.000.000
    } while(findBook(raizL, id) != NULL);  // Garantir que não existe
    return id;
}

//remover os Livros
NoBooks *removeBook(NoBooks *raiz, int id) {
    if (raiz == NULL) {
        printf("!!ERROR!!\n>Livro com ID (%d) não encontrado.\n", id);
        return NULL;
    }

    if (id < raiz->Livro->id)
        raiz->esq = removeBook(raiz->esq, id);
    else if (id > raiz->Livro->id)
        raiz->dir = removeBook(raiz->dir, id);
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
        NoBooks *pai = raiz;
        while (aux->esq != NULL) {
            pai = aux;
            aux = aux->esq;
        }

        *raiz->Livro = *aux->Livro;

        // Remove o sucessor
        if (pai == raiz)
            pai->dir = aux->dir;
        else
            pai->esq = aux->dir;

        free(aux->Livro);
        free(aux);
    }
    return raiz;
}


//listar os livros->in order
void ListBooks(NoBooks *RaizL){
    if(RaizL == NULL) return;
    ListBooks(RaizL->esq);
    printf("|ID: %d | título: %s | autor: %s | ano: %d | status : %s|\n", RaizL->Livro->id, RaizL->Livro->titulo, RaizL->Livro->autor, RaizL->Livro->ano, (RaizL->Livro->status == 0 ) ? "Disponível" : "Emprestado");
    if(RaizL->Livro->status == 1) printf("> Usuário com o livro: %s", RaizL->Livro->Emprestadoemail);
    ListBooks(RaizL->dir);
}

//listar os livros de um autor específico
void ListBooksperAuthor(NoBooks *raiz, char *autor){
    if(raiz == NULL) return;
    
    ListBooksperAuthor(raiz->esq, autor);

    if(raiz->Livro != NULL && autor != NULL) {
        if(strcmp(raiz->Livro->autor, autor) == 0){
            printf("|ID: %d | título: %s | ano: %d | status: %s|\n",
                raiz->Livro->id,
                raiz->Livro->titulo,
                raiz->Livro->ano,
                (raiz->Livro->status == 0) ? "Disponível" : "Emprestado");
    }
    }

    ListBooksperAuthor(raiz->dir, autor);
}

void ReleaseBook(NoBooks *RaizL){
    if(RaizL == NULL) return;
    ReleaseBook(RaizL->esq);
    ReleaseBook(RaizL->dir);

    if(RaizL->Livro) free(RaizL->Livro);
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
NoBooks *cadastrarLivro(NoBooks *raizeslivros){
    Books *NewL = (Books *)malloc(sizeof(Books));

    if(!NewL) {
        printf("Erro ao alocar memória\n");
        return raizeslivros;
    }
    
    NewL->id = nextIDbook(raizeslivros);

    printf("\n> CADASTRO DE LIVRO\n");
    printf("> ID gerado automaticamente: %d\n", NewL->id);
    lerString(NewL->titulo, 100, "Título: ");
    lerString(NewL->autor, 100, "Autor: ");
    NewL->ano = lerInteiro("Ano de publicação: ");
    NewL->status = 0;
    NewL->Emprestadoemail[0] = '\0';
    
    raizeslivros = InsertNewBook(raizeslivros, NewL);

    printf("> LIVRO CADASTRADO COM SUCESSO!\n");

    return raizeslivros;  
}

//consultar livro
void consultarLivro(NoBooks *raizeslivros){
    int opcao;
    printf("\n> CONSULTA DE LIVROS:\n");
    printf("| 1. Por código (ID)        |\n");
    printf("| 2. Por autor              |\n");
    printf("| 3. Listar todos os livros |\n");
    opcao = lerInteiro("Opção: ");
    
    if(opcao == 1){
        int id = lerInteiro("Digite o ID do livro: ");
        Books *acharlivro = findBook(raizeslivros, id);
        if(acharlivro != NULL){
            printf("\n> DADOS DO LIVRO:\n");
            printf("|   ID:  %d |\n", acharlivro->id);
            printf("| Título: %s |\n", acharlivro->titulo);
            printf("| Autor:  %s |\n", acharlivro->autor);
            printf("|   Ano:  %d |\n", acharlivro->ano);
            printf("| Status: %s |\n", (acharlivro->status == 0) ? "Disponível" : "Emprestado");

            if(acharlivro->status == 1)
                printf("| Usuário: %s |\n", acharlivro->Emprestadoemail);
        } else {
            printf("Livro não encontrado\n");
    }
    } else if(opcao == 2){
        char autor[100];
        lerString(autor, 100, "Digite o nome do autor: ");
        printf("\n> Livros de Sr.(a) %s\n", autor);
        ListBooksperAuthor(raizeslivros, autor);
    } else if(opcao == 3){
        if(raizeslivros == NULL) 
            printf("> Nenhum livro encontrado\n");
        else {
            printf("> Lista de todos os livros:\n");
            ListBooks(raizeslivros);
        }
    } else {

        printf("Operação inválida\n");
    }
}

//void atualizar o livro
void devolverLivro(NoBooks *raizeslivros){
    int id = lerInteiro("Digite o ID do livro: ");
    Books *livro = findBook(raizeslivros, id);
    if(livro == NULL){
        printf("Livro não encontrado\n"); 
        return;
    }
    if(livro->status == 0) {
        printf("O livro '%s' não está emprestado\n", livro->titulo); 
        return;
    }
    printf("Devolução do livro '%s', emprestado para %s\n", livro->titulo, livro->Emprestadoemail);
    livro->status = 0;
    livro->Emprestadoemail[0] = '\0';
    printf("Livro devolvido com sucesso!\n");
}

NoBooks* deleteBook(NoBooks *raizeslivros){
    int id = lerInteiro("Digite o ID do livro para remoção: ");
    Books *livro = findBook(raizeslivros, id);
    if(livro == NULL) {
        printf("Livro não encontrado\n"); 
        return raizeslivros;
    }
    if(livro->status == 1) {

        printf("!!ERROR!!\nO livro '%s' está emprestado para: %s\n", 
               livro->titulo, livro->Emprestadoemail); 
        return raizeslivros;
    }
    printf("Tem certeza que deseja excluir o livro '%s'?\n> (1-Sim / 0-Não): ", livro->titulo);
    int confirm = lerInteiro("1 - sim/0 - não");
    if(confirm == 1) {
        raizeslivros = removeBook(raizeslivros, id); 
        printf("Livro deletado com sucesso!\n");
    } else {
        printf("Operação cancelada\n");
    }
    return raizeslivros;
}

void loanBook(NoBooks *raizeslivros, Users *lista) {
    if (raizeslivros == NULL) {
        printf("Nenhum livro cadastrado.\n");
        return;
    }

    int id = lerInteiro("Digite o ID do livro: ");
    Books *livro = findBook(raizeslivros, id);
    if (livro == NULL) {
        printf("Livro não encontrado\n");
        return;
    }
    if (livro->status == 1) {
        printf("O livro '%s' já está emprestado para: %s\n", 
               livro->titulo, livro->Emprestadoemail);
        return;
    }

    char email[100];
    lerString(email, 100, "Digite o e-mail do usuário: ");

    Users *usuario = consultaUser(lista, email);
    if (usuario == NULL) {
        printf("Usuário não cadastrado. Empréstimo cancelado.\n");
        return;
    }

    livro->status = 1;
    strcpy(livro->Emprestadoemail, email);
    printf(" Empréstimo realizado com sucesso!\n");
    printf("  Livro: %s\n", livro->titulo);
    printf("  Usuário: %s\n", email);
}

void updatebook(NoBooks *raizeslivros){
    int id = lerInteiro("Digite o ID do livro: ");
    Books *livro = findBook(raizeslivros, id);
    if(livro == NULL) {
        printf("Livro não encontrado\n"); 
        return;
    }
    printf("\n> ATUALIZANDO LIVRO ID %d\n", id);
    printf("| Título atual: %s |\n", livro->titulo);
    printf("| Autor atual: %s  |\n", livro->autor);
    printf("|   Ano atual: %d  |\n", livro->ano);

    printf("\n> O que deseja alterar?\n");
    printf("| 1. Título |\n");
    printf("| 2. Autor  |\n");
    printf("| 3. Ano    |\n");
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
void liberarUsuarios(Users *lista) {
    Users *aux;
    while (lista != NULL) {
        aux = lista;
        lista = lista->next;
        free(aux);
    }
}

//Usuarios rhuan


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


void atualizaUsuarios(Users *lista, char *email){
    Users *usuario = consultaUser(lista, email);
    if (usuario == NULL){
        printf("Usuario não encontrado.\n");
        return;
    }
    lerString(usuario->nome, 100, "Digite o novo nome usuario: ");
    printf("Nome atualizado com sucesso."); //Lê a linha inteira, inclusive espaços.O espaço antes do % faz o scanf ignorar o '\n' que ficou no buffer.99 evita escrever além do tamanho do vetor.
}

Users *excluirUsuario(Users *lista, NoBooks *raizLivros, char *email) {

    if (usuarioTemEmprestimo(raizLivros, email)) {
        printf("Usuario não pode ser excluido: possui livros emprestados.\n");
        return lista;
    }

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
int usuarioTemEmprestimo(NoBooks *raiz, char *email) {
    if (raiz == NULL) return 0;

    if (raiz->Livro != NULL &&raiz->Livro->status == 1 && strcmp(raiz->Livro->Emprestadoemail, email) == 0) {
        return 1;
    }

    return usuarioTemEmprestimo(raiz->esq, email) || usuarioTemEmprestimo(raiz->dir, email);
}