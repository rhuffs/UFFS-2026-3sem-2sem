#include <stdio.h>
#include <stdlib.h>
// Lista dupla
struct tld{
  int n;
  struct tld *next, *prev;};
typedef struct tld ld;
typedef struct {
  ld *head;
  ld *tail;
} sent;

// Fila
struct tq {
  int n;
  struct tq *next;};
typedef struct tq q;
typedef struct {
  q *head;
  q *tail;
} queue;

queue getQeue(sent st){
    queue *new = (queue *)malloc(sizeof(queue));
    new->head = NULL;
    new->tail = NULL;
    ld *aux;
    for(aux = st.head; aux != NULL; aux = aux->next){
        
    }
}