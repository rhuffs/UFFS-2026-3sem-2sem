#include <stdlib.h>
#include <stdio.h>
struct tpoint {						
	int x,y;
	char c;
};
typedef struct tpoint point;
//
struct list_points{
	point p;
	struct list_points *next,*prev;
};
typedef struct list_points listp;
//
struct tsent {
	listp *head, *tail;
};
typedef struct tsent sent;
//
void initList(sent *s)
{
	s->head=NULL;
	s->tail=NULL;
}

point getValues()
{
	point p;
	printf("Informe (x y c): ");
	scanf("%d %d %c",&p.x,&p.y,&p.c);
	return p;
}
//
void getValuesP(point *p)
{
	printf("Informe (x y c): ");
	scanf("%d %d %c",&p->x,&p->y,&p->c);
	getchar();
}
//
void insertEnd(sent *s, point p)
{
	listp *lp;
	lp=(listp *)malloc(sizeof(listp)); // 1st step
	lp->p=p;                  //
	lp->next=NULL;            // 2nd step
	lp->prev=NULL;             //
	if (s->head==NULL) // or s->tail==NULL
	{
		s->head=lp;
		s->tail=lp;
		return;
    }
    s->tail->next=lp;
    lp->prev=s->tail;
    s->tail=lp;
    return;
}
//
void listPoints(sent s)
{
	listp *aux;
	for (aux=s.head;aux!=NULL;aux=aux->next) {
		printf("(%d, %d, %c)\n",aux->p.x, aux->p.y, aux->p.c);
	}
	return;
}
//
void deletePoint(sent *s, point p)
{
	listp *lp;
	for (lp=s->head;lp!=NULL;lp=lp->next)
		if (lp->p.x==p.x && lp->p.y==p.y && lp->p.c==p.c)
			break;
    if (lp==NULL) {
		printf("(%d, %d ,%c) Not Found!\n",p.x,p.y,p.c);
		return;
	}
	if (s->head==s->tail)
	{
		free(lp);
		initList(s);
		return;
	}
	if (lp==s->head)
	{
		s->head=s->head->next;
		s->head->prev=NULL;
		free(lp);
		return;
    }
    if (lp==s->tail)
    {
		s->tail=s->tail->prev;
		s->tail->next=NULL;
		free(lp);
		return;
    }
    lp->prev->next=lp->next;
    lp->next->prev=lp->prev;
    free(lp);
    return;
}

int main()
{
	sent s;
	//
	initList(&s);
	int op=1;
	point p;
	while (op!=0)
	{
	   printf("1-Insere fim\n2-Insere Meio\n3-Lista\n4-Exclui\n0-Sai\n");
	   scanf("%d",&op);
	   switch (op) {
		   case 1: p=getValues();
		           insertEnd(&s,p);
		           break;
		   case 3: listPoints(s);
		           break;
		   case 4: getValuesP(&p);
		           deletePoint(&s,p);
		           break;
	   }
	}
	return 0;
}

//malware aqui