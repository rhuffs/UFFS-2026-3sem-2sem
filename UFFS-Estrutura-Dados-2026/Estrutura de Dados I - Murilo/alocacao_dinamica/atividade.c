#include <stdio.h>
#include <stdlib.h>

// typedef struct{
//     int value;
//     LISTA *next;
// }LISTA;

// LISTA *getlist(int *v, int t){
//     LISTA *p, *aux, *f == NULL;
//     fot(int i = 0; i < t; i++){
//         p = (LISTA *)malloc(sizeof(LISTA));
//         p->value = v[i];
//         p->next = NULL;
//         if(f == NULL){
// 			f = p;
// 			aux = p;
//         }
//         else{
// 			aux->next = p;
// 			aux = p;
// 		}
		
//     }
//     return f;
// }

// LISTA *retornaPares(LISTA *f){
// 	LISTA *aux, *P, *fp = NULL, *ant;
// 	for(aux = f; aux != NULL; aux= aux->next){
// 		if(aux->value % 2 == 0){
// 			P = (LISTA *)malloc(sizeof(LISTA));
// 			P->value = aux->value;
// 			P->next = NULL;
// 			if (fp == NULL){
// 				fp = P;
// 				ant = P;
// 			}
// 			else{
// 				ant->next = P;
// 				ant = P;
// 			}
// 		}
// 	}
// 	return fp;
// }

// int main(){
	
	

// }
#include <stdlib.h>
#include <stdio.h>

struct tlist {
   int value;
   struct tlist *next;
};
typedef struct tlist list;

list *getEven(list *f)
{
	list *new, *naux, *nf=NULL, *faux;
	for (faux=f;faux!=NULL;faux=faux->next) {
		if (faux->value%2==0)
		{
			new=(list *)malloc(sizeof(list)); //1
			new->value=faux->value; //2
			new->next=NULL; //2
			if (nf==NULL) //3
			{
				nf=new;
				naux=new;
			} else {
				naux->next=new;
				naux=new;
			}
	    }
	}
	return nf;
}

list *intersection(list *l1, list *l2){
	list *first = NULL,*L1aux, *L2aux, *newP, *newnewaux;
	for(L1aux = l1; L1aux != NULL; L1aux = L1aux->next){
		for(L2aux = l2; L2aux != NULL; L2aux = L2aux->next){
			if(L1aux->value == L2aux->value){
				newP = (list *)malloc(sizeof(list));
				newP->value = L2aux->value;
				newP->next = NULL;
				if(first == NULL){
					first = newP;
					newnewaux = newP;
				}
				else{
					newnewaux->next = newP;
					newnewaux = newP;
				}
			}
		}
	}
	return first;
}


//
int main()
{
	list *l, *l2,*first=NULL, *first2 = NULL;
	first = getEven;
	for (l=first;l!=NULL;l=l->next)
	  printf("%d\n",l->value);
	for (l2=first2;l2!=NULL;l2=l2->next)
	  printf("%d\n",l2->value);
	printf("=======\n");
	first=intersection(first, );
	for (l=first;l!=NULL;l=l->next)
	  printf("%d\n",l->value);
	return 0;
}
