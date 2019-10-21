#include <stdio.h>
#include <stdlib.h>

#include <conio.h>

#include "llrb.h"

int main(int argc, char *argv[]) {
	ArvoreRB* raiz = NULL;
	
	int i, N = 10, dados[10] = {1,2,3,4,5,6,7,8,9,10};
	int dados2[9] = {0,3,6,77,123,2,1,22,11};

	for (i = 0 ; i<9;i++){
		InsereNaArvore(&raiz,dados2[i]);
	}
	
	printf("Pre ordem: \n");
	PreOrdem(raiz);
	
	RemoveDaArvore(&raiz,11);
	
	printf("\n\nEm ordem: \n");
	EmOrdem(raiz);
	
	RemoveDaArvore(&raiz,0);
	
	printf("\n\nEm ordem: \n");
	EmOrdem(raiz);
	
	InsereNaArvore(&raiz,10);
	
	printf("\n\nEm ordem: \n");
	EmOrdem(raiz);
	
	
	
	return 0;
}

