#include <stdio.h>
#include <stdlib.h>

struct tlist {
   int value;
   struct tlist *next;
};
typedef struct tlist list;

list *