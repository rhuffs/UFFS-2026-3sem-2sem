Trabalho T2
Descrição:

Nesta tarefa, você deverá implementar um tipo abstrato de dado (TAD) para manipular datas:

- O arquivo de cabeçalho deverá se chamar data.h

- O arquivo com a implementação das funções deverá se chamar data.c

- A estrutura deverá conter, pelo menos, 3 atributos: dia, mês e ano (e algum outro se você achar necessário)

- Funções a serem implementadas:

---- setDate (atribui dia, mês e ano para o tipo data criado), getDate (retorna o dia ou o mês ou o ano de uma data passada como parâmetro. O tipo de retorno deve ser passado como parâmetro também), showDate (mostra a data em um formato amigável para o usuário), dataComp (recebe duas datas como parâmetro é retorna 1 se a primeira data é maior que a segunda, -1 caso contrário e 0 se forem iguais), getDiff (recebe duas datas como parâmetro é retorna a diferença absoluta de dias entre elas. Como absoluto é: retornar sempre valores positivos), isLeapYear (retorna 1 se o ano da data passada por parâmetro é bissexto, e 0 se não for), getDayFromYear (deve retornar o número de dias trasncorridos desde o início do ano até a data passada como parâmetro).

- Gerar um ZIP apenas com o .h. e .c e o nome deverá ser a sua matrícula.

Exemplo de uso:

#include <stdio.>

#include "data.h"

int main() {

  data d1, d2;

  setDate(&d1,10,10,2026);

  setDate(&d2,1,11,2026);

  showDate(d1);

  printf("Ano: %d\n",getDate(d2,'Y')); // Y define ano

  printf("Diferença: %d dias\n",getDiff(d1,d2));

  return 0;

}

SAIDA:

10/10/2026

Ano: 2026

Diferença: 22 dias