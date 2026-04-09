#include <stdio.h>
#include <data.h>


void setDate(data *data, int d, int m, int a){
    data->dia = d;
    data->mes = m;
    data->ano = a;
}

int getDate(data d1, char info ){
    if (info == "D") return d1.dia;
    if (info == "M") return d1.mes;
    if (info == "Y") return d1.ano;
    printf("Nao é um valor válido");
    return 0;
}

void showDate(data d1){
    printf("%d / %d / %d", d1.dia, d1.mes, d1.ano);
}

int dataComp(data d1, data d2){
    if (d1.ano > d2.ano) return 1;
    else if (d1.ano < d2.ano) return -1;
    
    if (d1.mes > d2.mes) return 1;
    else if (d1.mes < d2.mes) return -1;

    if (d1.dia > d2.dia) return 1;
    else if (d1.dia < d2.dia) return -1;

    return 0;
}

int isLeapYear(data d1){
    
    if (d1.ano % 100 == 0){
        if (d1.ano % 400 == 0){
            return 1;
        } else return 0;  
    }
    if (d1.ano % 4 == 0 ){
        return 1;
    }

    return 0;

}


int getDaysBeforeMonth(data d1){
    if (isLeapYear(d1)){
        if (d1.mes == 1) return 0;
        if (d1.mes == 2) return 31;
        if (d1.mes == 3) return 60;
        if (d1.mes == 4) return 91;
        if (d1.mes == 5) return 121;
        if (d1.mes == 6) return 152;
        if (d1.mes == 7) return 182;
        if (d1.mes == 8) return 213;
        if (d1.mes == 9) return 244;
        if (d1.mes == 10) return 274;
        if (d1.mes == 11) return 305;
        if (d1.mes == 12) return 335;

    }
    if (d1.mes == 1) return 0;
    if (d1.mes == 2) return 31;
    if (d1.mes == 3) return 59;
    if (d1.mes == 4) return 90;
    if (d1.mes == 5) return 120;
    if (d1.mes == 6) return 151;
    if (d1.mes == 7) return 181;
    if (d1.mes == 8) return 212;
    if (d1.mes == 9) return 243;
    if (d1.mes == 10) return 273;
    if (d1.mes == 11) return 304;
    if (d1.mes == 12) return 334;

    return 0;


}

int getDayFromYear(data d1){
    int diaDoAno;
    diaDoAno = getDaysOfMonth(d1) + d1.dia;
    return diaDoAno;
}

int getDiff(data d1, data d2){
    int totalDia;
    if (dataComp(d1,d2) == 1){
        
    }
}
