#include <stdio.h>
#include "data.h"

int diasMes[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

// apontar os valores para atribui-los
void setDate(data *date, int d, int m, int a)
{
    date->dia = d;
    date->mes = m;
    date->ano = a;
}

// só imprime o resultado no terminal
void showDate(data date)
{
    printf("\nData: %d/%d/ %d\n ", date.dia, date.mes, date.ano);
}

// apenas retorna o mês(M), dia(D), ano(Y) selecionado a partir do caractere
int getDate(data date, char E)
{
    if (E == 'M')
        return date.mes;
    if (E == 'D')
        return date.dia;
    if (E == 'Y')
        return date.ano;
    printf("Valor não válido");
    return 0;
}

//verifica se o ano é bissexto
int isLeapYear(data D)
{
    if ((D.ano % 4 == 0 && D.ano % 100 != 0) || (D.ano % 400 == 0)) return 1;
    return 0;
}

//retorna os dias trancorridos desde o início do ano até a data passada como parâmetro
int getDayFromYear(data D)
{
    int total = D.dia;

    for (int i = 0; i < D.mes -1; i++)
    {
        total += diasMes[i];
    }

    if (D.mes > 2 && isLeapYear(D) == 1) total++;
    return total;
}

/*função para checar a diferença entre elas:
return 0 se for as duas igual;
return 1 se d1 > d2;
return-1 se d1 < d2;
*/
int dataComp(data d1, data d2)
{
    if (d1.ano == d2.ano)
    {
        if (d1.mes == d2.mes)
        {
            if (d1.dia == d2.dia) return 0;

            else if (d1.dia > d2.dia) return 1;

            else return -1;
        }

        else if (d1.mes > d2.mes) return 1;

        else return -1;
    }
    
    else if (d1.ano > d2.ano) return 1;
    
    else return -1;
}


/*essa função retorna TODOS os dias que aconteceram a partir do ano 0 até o ano colocado
exemplo:
 enviou uma data que é de 2026, de 0 até 2026 será: 739.994 dias
*/
int totalDaysyear(data D)
{
    int totaldia = getDayFromYear(D);
    data ls;
    ls.ano = 0;
    ls.mes = 0;
    ls.dia = 0;
    for (int i = 0; i <= D.ano; i++)
    {
        ls.ano = i;
        if (isLeapYear(ls) == 1) totaldia += 366;
        else totaldia +=365;
    }
    return totaldia;
}

/*Passo a Passo do getDiff:
-Cria duas variáveis do timpo inteiro para receber o número de dias do 0 até o ano colocado
-chama a função dataComp para 
*/
int getDiff(data date1, data date2)
{
    int tdias1 = totalDaysyear(date1);
    int tdias2 = totalDaysyear(date2);

    if(dataComp(date1, date2) == 1) return tdias1 - tdias2;
    else return tdias2 - tdias1;
}