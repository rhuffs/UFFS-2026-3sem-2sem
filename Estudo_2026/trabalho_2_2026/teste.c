#include <stdio.h>

#include "data.h"

int main() {

  data d1, d2;

  setDate(&d1,11,9,2011);

  setDate(&d2,12,5,2007);

  showDate(d1);
  showDate(d2);

  printf("Ano: %d\n",getDate(d1,'Y')); // Y define ano
  printf("Mês: %d\n",getDate(d1,'M')); // Y define ano
  printf("Dia: %d\n",getDate(d1,'D')); // Y define ano
  printf("Ano: %d\n",getDate(d2,'Y')); // Y define ano
  printf("Mês: %d\n",getDate(d2,'M')); // Y define ano
  printf("Dia: %d\n",getDate(d2,'D')); // Y define ano
  
  if (isLeapYear(d1))
  {
    printf("é um ano bissexto \n");
  } else {
    printf("Não é bissexto\n");
  }
  
  if (isLeapYear(d2))
  {
    printf("é um ano bissexto \n");
  } else {
    printf("Não é bissexto\n");
  }
  

  printf("Dias passados desde o inicio do ano : %d\n",getDayFromYear(d1));
  printf("Dias passados desde o inicio do ano : %d\n",getDayFromYear(d2));
  

  printf("Diferença: %d dias\n",getDiff(d1,d2));
  printf("Diferença: %d dias\n",getDiff(d2,d1));

  return 0;

}