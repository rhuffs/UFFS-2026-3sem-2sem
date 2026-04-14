#include <stdio.h>

typedef struct
{
    int dia;
    int mes;
    int ano;
} Data;

Data constroiData(int dia, int mes, int ano)
{
    Data d;
    d.dia = dia;
    d.mes = mes;
    d.ano = ano;
    return d;
}

int extraiDia(Data data)
{
    return data.dia;
}

int compararData(Data data1, Data data2)
{
    if (data1.ano < data2.ano)
    {
        return -1;
    }
    else if (data1.ano == data2.ano){
        if(data1.mes < data2.mes){
            return -1;
        }
        else if(data1.mes == data2.mes){
            if(data1.dia < data2.mes){
                return -1;
            }
            else if (data1.dia == data2.dia){
                return 0;
            }
        }
    }
    else{return 1;};
}

int main()
{
    // Usamos uma struct para armazenar uma coleção de dados de tipos possivelmente diferentes (heterogêneos)
    // Os elementos (membros) de uma struct podem ser de tipos diferentes
    // Para selecionar um elemento de uma struct, devemos especificar o caminho até o elemento: variavel_estrutura.elemento

    // funciona a mesma coisa que nem uma operação normal, porém, como uma organização, exemplos:
    // data1.dia = 10;
    // printf("%i", data2.ano);
    // e até
    // scanf("%d", &data1.mes);
    Data data1;
    Data data2;
    data1 = constroiData(11,9,2011);
    data2 = constroiData(11,9,2011);
    printf("%i", compararData(data1, data2));
    
    //TAD(Tipo Abstrado de Dados)
    
}