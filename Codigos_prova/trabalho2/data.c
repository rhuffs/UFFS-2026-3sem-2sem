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

int dataComp(data *d1, data *d2){
    if (d1->ano > d2->ano){
        return 1;
    } else if(d1->ano == d2->ano){
        if (d1->mes > d2->mes){
            return 1;
        } else if (d1->dia > d2->dia){
            return 1;
        }
    }
    return 0;
}

int getDiff(data d1, data d2){
    
}