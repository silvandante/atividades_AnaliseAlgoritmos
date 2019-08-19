#include <stdio.h>
#include <stdlib.h>

#define TAM 11

static int contRecursao = 0;
static int contFor = 0;

void MaxMinRecursivo(int vetor[], int min, int max, int indice){
	
	contRecursao++;
	
	if( vetor[indice] < min )
		min = vetor[indice];
	if( vetor[indice] > max )
		max = vetor[indice];
	if( indice < TAM-1 )
		MaxMinRecursivo(vetor, min, max, indice+1);
	else
		printf("RECURSIVO: \nMin: %d \nMax: %d", min, max);
}

void MaxMin(int vetor[], int tam){
	int i = 0;
	int max = vetor[0];
	int min = vetor[1];
	
	for (i = 2; i<= tam; i++){
		contFor++;
		if (vetor[i] > max){
			max = vetor[i];
		}
		if (vetor[i] < min){
			min = vetor[i];
		}
	}
	
	printf("\n\nNAO RECURSIVO: \nMin: %d \nMax: %d", min, max);
	
}


int main(){
	int vetor[TAM] = {9,2,1,8,6,3,4,5,0,7,-3};
	
	MaxMinRecursivo(vetor, vetor[0], vetor[0], 0);
	printf("\nContRecursao: %d",contRecursao);
	
	MaxMin(vetor,TAM);
	printf("\nContFor: %d\n",contFor);
	return 0;
}
