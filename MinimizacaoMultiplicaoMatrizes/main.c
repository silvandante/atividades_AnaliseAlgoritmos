#include <stdio.h>
#include <stdlib.h>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */
int MenorMultiplicacaoMatrizes(int matriz[], int i, int j){
	if (i==j){
		return 0;
	}
	
	int k, count;
	int min = INT_MAX;
	
	for (k=i; k<j; k++){
		count = MenorMultiplicacaoMatrizes(matriz, i, k) + MenorMultiplicacaoMatrizes(matriz, k+1, j) + matriz[i-1]*matriz[k]*matriz[j];
		
		if (count < min){
			min = count;
		}
	}
	
	return min;
}


int main(int argc, char *argv[]){
	int tamanho_matrizes[] = {30,35,15,5,10,20,25};

	int n = sizeof(tamanho_matrizes)/sizeof(tamanho_matrizes[0]);
	
	printf("Menor numero de multiplicacoes entre essa matriz: %d\n\n", MenorMultiplicacaoMatrizes(tamanho_matrizes, 1, n-1));

  	system("PAUSE");     
  	return 0;
}
