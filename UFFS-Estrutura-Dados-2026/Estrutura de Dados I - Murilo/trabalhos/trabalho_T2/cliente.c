#include <stdio.h>
#include "data.h"

int main()
{

  data d1, d2;

  setDate(&d1,9,4,2001);

  setDate(&d2,5,3,2001);

  showDate(d1);

  printf("Ano: %d\n",getDate(d2,'Y')); // Y define ano

  printf("Diferença: %d dias\n",getDiff(d1,d2));

  return 0;
}
