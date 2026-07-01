//lista simples para o usuário
typedef struct Usuario{
    char email[100];
    char nome[100];
    struct Usuario *next;
} Users;


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
void limparBuffer();// LLM
//-->scanf para string
int lerString(char *, int , char *);

//-->scanf para inteiro
int lerInteiro(char *);

//-->cadastrar o livro
NoBooks *cadastrarLivro(NoBooks *); 

//_>consultar o livro
void consultarLivro(NoBooks *raizeslivros);

//->>devolver o livro
void devolverLivro(NoBooks *raizeslivros);

//->remover o livro
NoBooks* deleteBook(NoBooks *raizeslivros); 
//-->emprestaro o livro
void loanBook(NoBooks *, Users *);

void updatebook(NoBooks *);

//Usuarios

//Cadastra usuarios
Users *CadastrarUsuarios(Users *,char *, char *);

//Consulta usuarios
Users *consultaUser(Users *, char *);

//Lista os empréstimos
void listarEmprestimos(NoBooks *, char *);

//Atualiza o nome de um usuario
void atualizaUsuarios(Users *, char *);

// Exclui um usuario
Users *excluirUsuario(Users *,NoBooks *, char *);

int usuarioTemEmprestimo(NoBooks *raiz, char *email);

void liberarUsuarios(Users *);
