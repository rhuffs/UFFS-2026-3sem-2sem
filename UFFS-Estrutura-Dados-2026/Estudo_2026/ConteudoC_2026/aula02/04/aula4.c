#include<stdio.h>
void troca(int *a , int *b){
    int aux;
    aux = *a;
    *a = *b;
    *b = aux;
    
}
void maior (int i1, int i2, int *p)
{  
	if (i1>i2) {*p=i1;}
	else       {*p=i2;}
}
int main()
{	
   int a=5, b=10, m;
   printf("a=%d b=%d\n",a,b);
   troca(&a,&b);
   printf("a=%d b=%d\n",a,b);
   maior(23,34,&m);
   printf("Maior: %d\n",m);
   return 0;
}   

//eu odeio aux :(
//cria uma variavel auxiliar
// a variavel auxiliar recebe o valor apontado por a
//o valor apontado por a recebe o valor apontado por b
//o valor apontado por b recebe a variavel auxiliar 
//que agora armazena o antigo valor de A