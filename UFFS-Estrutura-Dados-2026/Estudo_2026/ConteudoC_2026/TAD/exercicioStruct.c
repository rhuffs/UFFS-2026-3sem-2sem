#include <stdio.h>

typedef struct {
  int dia;
  int mes;
  int ano;
} Data;
Data constroiData(int dia, int mes, int ano) {
  Data data;
  data.dia = dia;
  data.mes = mes;
  data.ano = ano;
  return data;
}

int extraiaDia(Data d){
    return d.dia;
}


int comparaData(Data d1, Data d2){
    if (d1.ano < d2.ano){
        return -1;
    } 
    if (d1.ano > d2.ano){
        return 1;
    } 
    if (d1.mes < d2.mes){
        return -1;
    } 
    if (d1.mes > d2.mes){
        return 1;
    } 
    if (d1.dia < d2.dia){
        return -1;
    } 
    if (d1.dia > d2.dia){
        return 1;
    } 

    return 0;
}


int main(){
    Data d1;
    Data d2;
    d1 = constroiData(11,9,2011);
    d2 = constroiData(11,9,2011);
    printf("%d", extraiaDia(d1));
    printf("\n");
    printf("%d",comparaData(d1,d2));
}