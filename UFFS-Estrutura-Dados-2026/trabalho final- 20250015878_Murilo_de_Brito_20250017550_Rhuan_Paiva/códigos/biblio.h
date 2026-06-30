
//árvore para o usuário
typedef struct Usuario{
    char email[100];
    char nome[100];
} Users;

typedef struct Noparaousuario{
    Users *U;//->conseguir acessar a struct (Users)
    struct Noparaousuario *esq;
    struct Noparaousuario *direita;
} NoUser;

//árvore para o livro
typedef struct Livro{
    int id;
    char titulo[100];
    char autor[100];
    int ano;
    int status;//-> 0 = disponível, 1 = emprestado
    char Emprestadoemail[100];//->de quem emprestou
} Books;

typedef struct Noparaolivro{
    Books *Livro;//acessar o conteudo da struct(Books)
    struct Noparaolivro *esq;
    struct Noparaolivro *dir;
} NoBooks;

//-->allocar o novo livro no espaço de memoria
NoBooks *NoPlivro(Books *);

//-->inserir o livro novo na raiz dos livros
NoBooks *InsertNewBook(NoBooks *, Books *);

//-->Encontr o extremo do livro(mínimo ou máximo)
NoBooks* ExtremeBook(NoBooks *, int );

//-->Gera o próximo ID automaticamente
int nextIDbook(NoBooks *);

Books *findBook(NoBooks *, int );

//-->Remove o livro
NoBooks *removeBook(NoBooks *, int );

//-->listar os livros
void ListBooks(NoBooks *);

//-->listar os livros por autor
void ListBooksperAuthor(NoBooks *, char *);

//-->liberar os livros
void ReleaseBook(NoBooks *);

//-->limpa o buffer de entrada(ENTER)
void limparBuffer();

int lerString(char *, int , char *);

int lerInteiro(char *);

void cadastrarLivro();

void consultarLivro();

void devolverLivro();

