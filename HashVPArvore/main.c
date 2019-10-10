#include <stdio.h>
#include <stdlib.h>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */


struct no {
	int num;
	char color;
	
	struct no *esquerda;
	struct no *direita;
	struct no *pai;
	
};

void RotacaoEsquerda(struct no **raiz, struct no *x){
	struct no *y = x->direita;
	
	x->direita = y->esquerda;
	
	if(x->direita != NULL){
		x->direita->pai = x;	
	}
	
	y->pai = x->pai;
	
	if (x->pai == NULL){
		(*raiz) = y;
	} else {
		if(x == x->pai->esquerda){
			x->pai->esquerda = y;
		} else {
			x->pai->direita = y;
		}
	}
	
	y->esquerda = x;
	x->pai = y;
}

void RotacaoDireita(struct no **raiz, struct no *y){
	struct no *x = y->esquerda;
	
	y->esquerda = x->direita;
	
	if(x->direita != NULL){
		x->direita->pai = y;	
	}
	
	x->pai = y->pai;
	
	if (x->pai == NULL){
		(*raiz) = x;
	} else {
		if(y == y->pai->esquerda){
			y->pai->esquerda = x;
		} else {
			y->pai->direita = x;
		}
	}
	
	x->direita = y;
	y->pai = x;
}

void InsersaoFixUp(struct no **raiz, struct no *z){
	while ((z != *raiz)&&(z->pai->color ==  'V')){
		struct no *y;
		
		if (z->pai == z->pai->pai->esquerda){
			y = z->pai->pai->direita;
		} else {
			y = z->pai->pai->esquerda;
		}
		
		if (y->color == 'V'){
			y->color = 'P';
			z->pai->color = 'P';
			z->pai->pai->color = 'V';
			z = z->pai->pai;
		} else {
			if ((z->pai == z->pai->pai->esquerda)&&(z == z->pai->esquerda)){
				char ch = z->pai->color;
				z->pai->color = z->pai->pai->color;
				z->pai->pai->color = ch;
				RotacaoDireita(raiz,z->pai->pai);
			}
			
			if ((z->pai == z->pai->pai->esquerda)&&(z == z->pai->direita)){
				char ch = z->color;
				z->color = z->pai->pai->color;
				z->pai->pai->color = ch;
				RotacaoEsquerda(raiz,z->pai);
				RotacaoDireita(raiz,z->pai->pai);
			}
			
			if ((z->pai == z->pai->pai->direita)&&(z == z->pai->direita)){
				char ch = z->pai->color;
				z->pai->color = z->pai->pai->color;
				z->pai->pai->color = ch;
				RotacaoEsquerda(raiz,z->pai->pai);
			}
			
			if ((z->pai == z->pai->pai->direita)&&(z == z->pai->esquerda)){
				char ch = z->color;
				z->color = z->pai->pai->color;
				z->pai->pai->color = ch;
				RotacaoDireita(raiz,z->pai);
				RotacaoEsquerda(raiz,z->pai->pai);
			}
		}
		
	}
	
	(*raiz)->color = 'P';
}

void Inserir(struct no **raiz, int num){
	
	printf("\ninserindo %d\n", num);
	struct no *z = (struct no*)malloc(sizeof(struct no));
	
	z->num = num;
	z->esquerda = z->direita = z->pai = NULL;
	
	if (*raiz == NULL){
		z->color = 'P';
		(*raiz) = z;
		printf("inseriu %d\n", num);
	} else {
		struct no *y = NULL;
		struct no *x = (*raiz);
		
		while (x!=NULL){
			y = x;
			if (z->num < x->num){
				x = x->esquerda;
			} else {
				x = x->direita;
			}
		}
		z->pai = y;
		if (z->num > y->num){
			y->direita = z;
		} else {
			y->esquerda = z;
		}
		z->color = 'R';
		
		InsersaoFixUp(raiz, z);
		printf("inseriu %d\n", num);
	}
	
}

void EmOrdem(struct no *raiz)
{
    if (raiz == NULL)
        return;
    EmOrdem(raiz->esquerda);
    printf("%d ", raiz->num);
    EmOrdem(raiz->direita);
}

#define HASHTABLE_MAX 11

typedef struct item {
	int valor;
	struct item *proximo;
} item;


int GetPosicaoHash(int novo_valor){
	return novo_valor % HASHTABLE_MAX;
}

void InserirNaTabela (item **tabelahash, int novo_valor){
	int posicaoHash = GetPosicaoHash(novo_valor);
	
	if (tabelahash[posicaoHash] == NULL){
		tabelahash[posicaoHash] = malloc(sizeof(item*));
		
		struct no *raiz = NULL;
		
		Inserir(&raiz, novo_valor);
		
		tabelahash[posicaoHash] = raiz;
	} else {
		struct no *raiz = tabelahash[posicaoHash];
		Inserir(&raiz, novo_valor);
		
		tabelahash[posicaoHash] = raiz;
	}
}

void ImprimirTabela(item **tabelaHash){
	int i;
	for (i=0; i< HASHTABLE_MAX; i++){
		struct no *cabeca = tabelaHash[i];
		
		printf("%d: ", i);
		
		if (cabeca == NULL){
			printf("NULL \n");
		} else {
			struct no *raiz = cabeca;
			EmOrdem(raiz);
			printf("\n");
			/*while (atual != NULL){
				printf("%d \n", atual->valor);
				atual = atual->proximo;
			}*/
		}
	}
}

item** GetTabelahash(){
	item **tabelahash = calloc(HASHTABLE_MAX, sizeof(item*));
	return tabelahash;
}

int main(int argc, char *argv[]) {
	
	item **tabela = GetTabelahash();
	
	InserirNaTabela(tabela,1);
	InserirNaTabela(tabela,3);
	InserirNaTabela(tabela,10);
	InserirNaTabela(tabela,1);
	InserirNaTabela(tabela,3);
	InserirNaTabela(tabela,100);
	InserirNaTabela(tabela,11);
	InserirNaTabela(tabela,32);
	InserirNaTabela(tabela,10);
	
	InserirNaTabela(tabela,1);
	InserirNaTabela(tabela,13);
	InserirNaTabela(tabela,10);
	
	ImprimirTabela(tabela);
	
	
	return 0;
}
