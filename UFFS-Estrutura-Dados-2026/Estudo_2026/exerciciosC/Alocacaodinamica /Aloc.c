//~ // Nível 1 — Fundamentos (estrutura básica)
//~ // Crie a estrutura de um nó contendo:
//~ // valor
//~ // ponteiro para o próximo
//~ // Crie uma lista vazia.
//~ // Implemente:
//~ // Inserção no início
//~ // Implemente:
//~ // Impressão da lista
//~ // Insira 5 valores e imprima.

//~ //Nível 2 — Operações básicas
//~ //Inserir no final
//~ //Contar número de nós
//~ //Buscar um valor (retornar 1 ou 0)
//~ //Encontrar maior valor
//~ //Encontrar menor valor


//~ //Nível 3 — Manipulação
//~ //Inserir em posição específica
//~ //Remover primeiro elemento
//~ //Remover último elemento
//~ //Remover valor específico
//~ //Inverter a lista

//~ Nível 4 — Algoritmos
//~ Verificar se está ordenada
//~ Inserir mantendo ordenação
//~ Remover duplicados
//~ Encontrar elemento do meio
//~ Detectar ciclo (dois ponteiros)

//~ Nível 5 — Avançado
//~ Concatenar duas listas
//~ Intercalar duas listas
//~ Dividir lista ao meio
//~ Ordenar (Merge Sort)
//~ K-ésimo elemento a partir do final

//~ Desafios (nível prova pesada)
//~ Verificar se é palíndromo
//~ Rotacionar a lista k posições
//~ Remover nós com valor maior à direita
//~ Detectar interseção entre duas listas
//~ Lista com ponteiro para cauda (otimizada)


#include <stdio.h>
#include <stdlib.h>

typedef struct NO {
    int valor;
    struct NO *next;
} no;

no *insercaoInicio(no *f, int n){
    no *novo = NULL;
    novo = (no *)malloc(sizeof(no));
    novo->valor = n;
    novo->next = f;
    return novo;
}
no *insercaoFim(no *f, int n){
	no *aux, *novo = NULL;
	novo = (no *)malloc(sizeof(no));
	novo->valor = n;
	novo->next = NULL;
	if (f == NULL){
		f = novo;
		return novo;
	}
	
	for(aux = f; aux->next != NULL; aux = aux->next);
	aux->next = novo;
	return f;
	
	
}

int numeroNos(no *f){
	no *aux;
	int i = 0;
	for(aux = f; aux != NULL; aux = aux->next){
		i++;
	}
	return i;
	
}

int buscarNo(no *f, int valor){
	no *aux;
	for (aux = f; aux != NULL; aux = aux->next){
		if (aux->valor == valor) return 1;
	}
	return 0;
	
}

int encontrarMaior(no *f){
	if(f == NULL){
		return 0;
	}
	no *aux = NULL;
	int maior;
	maior = f->valor;
	for (aux = f; aux != NULL; aux = aux->next ){
		if(aux->valor > maior) maior = aux->valor; 
	}
	return maior;
}
int encontrarMenor(no *f){
	if(f == NULL){
		return 0;
	}
	no *aux = NULL;
	int menor;
	menor = f->valor;
	for (aux = f; aux != NULL; aux = aux->next ){
		if(aux->valor < menor) menor = aux->valor; 
	}
	return menor;
}



int main(){
    no *f = NULL;
    f = insercaoInicio(f, 10);
    f = insercaoInicio(f, 20);
    f = insercaoInicio(f, 30);
    f = insercaoInicio(f, 40);
    f = insercaoInicio(f, 50);
    f = insercaoFim(f, 60);
    


    for(no *aux = f ; aux!= NULL; aux = aux->next){
        printf("%d\n", aux->valor);
    }
	printf("%d\n",numeroNos(f));
    return 0;
}
