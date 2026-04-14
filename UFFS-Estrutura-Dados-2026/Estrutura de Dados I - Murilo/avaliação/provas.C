#include <stdio.h>
#include <string.h>
typedef struct{
    int A;
    int B;
    int C;
} Ltriangle;

typedef struct
{
	int inteiro;
	int decimal;
} reais;

Ltriangle setTria(int, int, int);
int istrgl(Ltriangle trg);



int logaritmo(int V)
{
    if(V <= 1) return 0;

    return 1 + logaritmo(V /2);
    
}

void showReal(reais Vreal)
{
	printf("%d,%02d\n", Vreal.inteiro,Vreal.decimal);
}

reais setreal(int n, int d)
{
	reais R;
	if(d < 0 || d > 99)
	{
		R.decimal = -1;
		R.inteiro = -1;
		return R;
	}
	R.decimal = d;
	R.inteiro = n;
	return R;
}

reais sumReal(reais vr1, reais vr2)
{
	reais mx;
	mx.inteiro = vr1.inteiro + vr2.inteiro;
	if(vr1.decimal + vr2.decimal > 99)
	{
		mx.inteiro ++;
		mx.decimal = (vr1.decimal + vr2.decimal) - 100;
	}
	else
	{
		mx.decimal = vr1.decimal + vr2.decimal;
	}
	return mx;
}

int main()
{
    //AVALIAÇÃO 1
        //1)
        printf("%d", logaritmo(42));
        
        //2)
        Ltriangle triangulo = setTria(16,20,30);
		printf("Seu triângulo: %d, %d, %d", triangulo.A, triangulo.B, triangulo.C);
		
		printf("Iremos checkar se é um triângulo");
		
		if(istrgl(triangulo) == 1) {printf("Parabéns, sua forma de triângulo é realmete válida slk\n");}
		else {printf("Definitivamente não é um triangulo certinho");}
		
		
		


    //AVALIAÇÃO 2
        //2
		reais vrea1 = setreal(1,70);
		reais vrea2 = setreal(2,45);
		showReal(vrea1);
		reais somatoria = sumReal(vrea1, vrea2);
		showReal(somatoria);
		
		
		
		
		return 0;
}

Ltriangle setTria(int LA, int LB, int LC){
    Ltriangle trg;
    trg.A = LA;
    trg.B = LB;
    trg.C = LC;
    return trg;
}

int istrgl(Ltriangle tria){
	if((tria.A + tria.B > tria.C) && (tria.B + tria.C > tria.A) && (tria.A + tria.C > tria.B)) return 1;
	else return 0;
}

