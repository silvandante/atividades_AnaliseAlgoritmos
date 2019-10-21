#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include "llrb.h"

int Cor (ArvoreRB *h){
	if (h==NULL){
		return BLACK;
	} else {
		return h->cor;
	}
}



void TrocaCor(ArvoreRB *h){
	h->cor = !h->cor;
	if (h->esquerda != NULL){
		h->esquerda->cor = !h->esquerda->cor;
	}
	if (h->direita != NULL){
		h->direita->cor = !h->direita->cor;
	}
}

ArvoreRB* RotacaoEsquerda (ArvoreRB *a){
	ArvoreRB *b = a->direita;
	a->direita = b->esquerda;
	b->esquerda = a;
	b->cor = a->cor;
	a->cor = RED;
	return b;
}
ArvoreRB* RotacaoDireita(ArvoreRB *a){
	ArvoreRB *b = a->esquerda;
	a->esquerda = b->direita;
	b->direita = a;
	b->cor = a->cor;
	a->cor = RED;
	return b;
}

ArvoreRB* Move2EsquerdaRED (ArvoreRB *h){
	TrocaCor(h);
	if (Cor(h->direita->esquerda) == RED){
		h->direita = RotacaoDireita(h->direita);
		h = RotacaoEsquerda(h);
		TrocaCor(h);
	}
	return h;
}



ArvoreRB* Move2DireitaRED (ArvoreRB *h){
	TrocaCor(h);
	if (Cor(h->esquerda->esquerda) == RED){
		h = RotacaoDireita(h);
		TrocaCor(h);
	}
	return h;
}
ArvoreRB* Balancear(ArvoreRB *h){
	//nó vermelho é sempre filho a esquerda
	if (Cor(h->direita) == RED){
		h = RotacaoEsquerda(h);
	}
	
	//filho da direita e neto da esquerda são vermelhos
	if ((h->esquerda != NULL) && (Cor(h->direita)==RED) && (Cor(h->esquerda->esquerda) == RED)){
		h = RotacaoDireita(h);
	}
	
	//2 filhos vermelhos, apenas inverte cor
	if ((Cor(h->esquerda)==RED)&&(Cor(h->direita)==RED)){
		TrocaCor(h);
	}
	
	return h;
}

ArvoreRB* InsereNo(ArvoreRB* h, int valor, int *resp){
	
	if (h==NULL){
		
		ArvoreRB *novo;
		novo = (ArvoreRB*)malloc(sizeof(ArvoreRB));
		
		if (novo == NULL){
			*resp = 0;
			return NULL;
		}
		
		novo->valor = valor;
		novo->cor = RED;
		novo->direita = NULL;
		novo->esquerda = NULL;
		*resp = 1;
		return novo;
	}
	
	if (valor == h->valor){
		*resp = 0; //valor duplicado
	} else {
		if (valor < h->valor){
			h->esquerda = InsereNo(h->esquerda, valor, resp);
		} else {
			h->direita = InsereNo(h->direita,valor,resp);
		}
	}
	
	if ((Cor(h->direita) == RED)&&(Cor(h->esquerda) == BLACK)){
		h = RotacaoEsquerda(h);
	}
	
	if ((Cor(h->esquerda) == RED)&&(Cor(h->esquerda->esquerda) == RED)){
		h = RotacaoDireita(h);
	}
	
	if ((Cor(h->esquerda) == RED) && (Cor(h->direita) == RED)){
		TrocaCor(h);
	}
	
	return h;
}

int InsereNaArvore(ArvoreRB **raiz, int valor){
	int resposta;
	
	*raiz = InsereNo(*raiz, valor, &resposta);
	
	if ((*raiz) != NULL){
		
		(*raiz)->cor = BLACK;
	}
	
	return resposta;
}

ArvoreRB* RemoverMenor(ArvoreRB *h){
	if (h->esquerda == NULL){
		free(h);
		return NULL;
	}
	if ((Cor(h->esquerda) == BLACK) && (Cor(h->esquerda->esquerda)==BLACK)){
		h = Move2EsquerdaRED(h);
	}	
	h->esquerda = RemoverMenor(h->esquerda);
	
	return Balancear(h);
}

ArvoreRB* ProcuraMenor(ArvoreRB*atual){
	ArvoreRB *no1 = atual;
	ArvoreRB *no2 = atual->esquerda;
	
	while (no2 != NULL){
		no1 = no2;
		no2 = no2->esquerda;
	}
	
	return no1;
}

int ConsultaArvore(ArvoreRB **raiz, int num){
	ArvoreRB *aux = *raiz;
	
	while (aux){
		if (num == aux->valor){
			return 1;
		}
		if (num > aux->valor){
			aux = aux->direita;
		} else {
			aux = aux->esquerda;
		}
		
	}
	
	return 0;
    
}

ArvoreRB* RemoveNo(ArvoreRB*h, int valor){
	if (valor < h->valor){
		if ((Cor(h->esquerda) == BLACK) && (Cor(h->esquerda->esquerda)==BLACK)){
			h = Move2EsquerdaRED(h);
		}
		
		h->esquerda = RemoveNo(h->esquerda, valor);
	} else {
		if (Cor(h->esquerda) == RED){
			h = RotacaoDireita(h);
		}
		
		if ((valor == h->valor)&&(h->direita==NULL)){
			free(h);
			return NULL;
		}
		
		if ((Cor(h->direita) == BLACK)&&(Cor(h->direita->esquerda) == BLACK)){
			h = Move2DireitaRED(h);
		}
		
		if (valor == h->valor){
			ArvoreRB*x = ProcuraMenor(h->direita);
			h->valor = x->valor;
			h->direita = RemoverMenor(h->direita);
		} else {
			h->direita = RemoveNo(h->direita,valor);
		}
	}
	return Balancear(h);
}

int RemoveDaArvore(ArvoreRB **raiz, int valor){
	if (ConsultaArvore(raiz,valor)==1){
		ArvoreRB *h = *raiz;
		
		*raiz = RemoveNo(h,valor);
		if ((*raiz) != NULL){
			(*raiz)->cor = BLACK;
		}
		return 1;
	} else {
		return 0;
	}
}


void PreOrdem(ArvoreRB *raiz){

    if(raiz) {  
        //  Mostra os elementos em pré-ordem
        if(raiz->cor == RED){
           
            printf("RED[%d] ", raiz->valor);  
        }
        else
            printf("BLACK[%d] ", raiz->valor);

        PreOrdem(raiz->esquerda);  
        PreOrdem(raiz->direita);   
    } 
}

void EmOrdem(ArvoreRB *raiz){

    if(raiz) {  
        //  Mostra os elementos em pré-ordem
        EmOrdem(raiz->esquerda);
        if(raiz->cor == RED){
           printf("RED[%d] ", raiz->valor);  
        }
        else
            printf("BLACK[%d] ", raiz->valor);  
        EmOrdem(raiz->direita);   
    } 
}


