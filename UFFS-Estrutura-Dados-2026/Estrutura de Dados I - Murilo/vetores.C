#include <stdio.h>
#include <string.h>//com isso, abre leks para a utilização de frases

void printV(int *v, int l){//mesmo o v sendo um vetor, será um ponteiro tbm
            //ou v[]
    int i;
    for(i = 0; i<l; i++){
        printf("%d\n", v[i]);
    }
}//estará entregando o endereço da memória

//função string

void printVI( int *v, int tam){
    for(int i = 0; i < tam; i++){printf("%d\n", v[i]);}
}
int main(){
    
    int vetor[4]= {1,2,3,4};
    //vetores são ponteiros disfarçados, ou seja, haverá espaços de endereçamento da RAM
    //se meter um scanf para ler uma string em um char, virou lost media

    int v[5] = {1,2,3,4,5};
    printV(v,5);
    // para conseguiur achar o tamanho do vetor
        //sizeof = 4 bits * tamanho do vetor
    int tamV = sizeof(v);
    printf("%i\n", tamV);
    int divtamV = tamV/sizeof(int);
    printf("%i", divtamV);

    //para imprimir uma palavra, sempre terá uma operação vazia que é ('\0')
    //st = "teste" ERRADO
    char st[5];
    st [0] = 't';
    st [1] = 'e';
    st [2] = 's';
    st [3] = 't';
    st [4] = 'e';
    //funcional, porém, chato, o que pensaram? Criaram a biblioteca chamada -olha lá encima do aqruivo-
    char ts;
    strcpy(ts, "hoje, eu acordei com pé direito e disse hj"); 
    // strcpy; strcmp; strlen; strcat
    //strcpy(destino, origem) (String Copy): Copia o conteúdo da string origem para a string destino, substituindo o conteúdo anterior.
    //strcat(destino, origem) (String Concatenate): Concatena (junta) a string origem ao final da string destino.
    //strlen(string) (String Length): Retorna o tamanho (número de caracteres) da string, sem contar o caractere nulo terminador \0.
    //strcmp(s1, s2) (String Compare): Compara duas strings caractere por caractere (ASCII). Retorna 
    //se forem iguais, um valor menor que 
    //se , e maior que se
    //exemplos:
    char s;
    strcpy(s, "Tomorow");
    for (int i = 0; i < strlen(s); i++){printf("%c", s[i]);}// ou printf("%s", s);
    // ou 
    // funções para imprimir, estarão acima

    return 0;
}