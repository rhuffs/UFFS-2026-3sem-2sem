    #include <stdio.h>
    #include <stdlib.h>

    typedef struct valor{
        int  value;
        struct valor *next;
        
    } value;

    value *insere(value *f, int valor, int cs, int id){
        value *aux, *novo;
        novo = (value *)malloc(sizeof(value));
        novo->value = valor;
        novo->next = NULL;
        if (f == NULL) return novo;
        if (cs == 1){
            
            novo->next = f;
            return novo;
        }
        if (cs == 2){
            for (aux = f; aux->next !=NULL; aux = aux->next);
            aux->next = novo;
            return f;
        }else {
            for(aux = f; aux->next != NULL; aux = aux->next){
                if(aux->value == id){
                    novo->next = aux->next;
                    aux->next = novo;
                    return f;
                }

            }
            return 0;
        }
        
    }

    int main(){
        value *f = NULL, *aux = NULL;
        f = insere(f,30,1,0);
        f = insere(f,12,1,0);
        f = insere(f,7,1,0);
        f = insere(f,5,1,0);
        f = insere(f,10,1,0);
        f = insere(f,31,2,0);
        f = insere(f,32,2,0);
        f = insere(f,32,2,0);
        f = insere(f,4,3,10);
        f = insere(f,7,3,32);

        for ( aux = f; aux != NULL; aux= aux->next){
            printf("%d\n",aux->value );
        }

        free(aux);
        return 0;
    }