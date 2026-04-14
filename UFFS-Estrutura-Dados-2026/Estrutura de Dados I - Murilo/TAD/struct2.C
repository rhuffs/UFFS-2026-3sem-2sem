#include <stdio.h>

typedef struct{
    int day, moth,year;
} tdate;
// ou
struct date{
    int day, moth,year;
};
//OU
struct dayti{
    int day, moth, year;
}; typedef struct dayti datei;
//OU 
typedef struct date{
    int day, moth, year;
} datebaio;

struct tfriend{
    char name[50], email[50];
    struct date dbirth;//aqui, é preciso utilizar uma struct que possue o nome da função declarada no ínicio
};

struct tteste{
    int a;
    struct tteste infinito;
}; typedef struct tteste teste;

int main(){
    tdate d[10];//podemos criar um vetor do tipo tdate
    d[0].day = 5;
    
    datei *dp;
    //int *dp;
    
    //dp = *5 ERRADO
    dp->day = 2;//se quiser passar como parâmetro
    
    return 0;
}