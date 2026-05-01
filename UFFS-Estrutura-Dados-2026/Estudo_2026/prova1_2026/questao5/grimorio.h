typedef struct magia{
    int poder_magico;
    char nome_feitico [20];
    struct magia *next;
} Grimorio;


Grimorio* cria_grimorio();

Grimorio* aprende_feitico(Grimorio* g, char *nome_feitico, int poder_magico);

void lista_feitico(Grimorio *g);