
//apenas para o usuário
typedef struct Usuario{
    char email[100];
    char nome[100];
} Users;

typedef struct Noparaousuario{
    Users *U;//->conseguir acessar a struct (Users)
    struct Noparaousuario *esq;
    struct Noparaousuario *direita;
} NoUser;

//apenas para o livro
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

//allocar o novo livro no espaço de memoria
NoBooks *NoPlivro(Books *);

//inserir o livro novo na raiz dos livros
NoBooks *InsertNewBook(NoBooks *, Books *);

