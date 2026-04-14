#include <stdio.h>
#include <string.h>



int NumVogais(char *v){
    int tam = strlen(v);
    int contagemVogal = 0;
    for(int i = 0; i < tam; i++){
        if (v[i]== 'a' || v[i]== 'e' || v[i]== 'i' || v[i]== '0' || v[i]== 'u' ){
            contagemVogal++;
        }
    }
   

    return contagemVogal;
}


void revesprint(char *v,  int Tam){
    for (int i = Tam; i >= 0; i--){
        printf("%c", v[i]);
    }
    printf("\n");
}


int main (){
    char Str[8];
    strcpy(Str, "cadeira");
    revesprint(Str,strlen(Str) );
    char pt2[100];
    scanf("%s",pt2 );
    revesprint(pt2, strlen(pt2));
    printf("%d",NumVogais(pt2));
}

