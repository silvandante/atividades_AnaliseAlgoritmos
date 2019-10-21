#define RED 1
#define BLACK 0

typedef struct NO{
	int valor;
	struct NO *esquerda;
	struct NO *direita;
	int cor;
}ArvoreRB;

int Cor (ArvoreRB *h);
void TrocaCor(ArvoreRB *h);
ArvoreRB* RotacaoEsquerda (ArvoreRB *a);
ArvoreRB* RotacaoDireita(ArvoreRB *a);
ArvoreRB* Move2EsquerdaRED (ArvoreRB *h);
ArvoreRB* Move2DireitaRED (ArvoreRB *h);
ArvoreRB* Balancear(ArvoreRB *h);
ArvoreRB* InsereNo(ArvoreRB *h, int valor, int *resp);
int InsereNaArvore(ArvoreRB **raiz, int valor);
ArvoreRB* RemoverMenor(ArvoreRB *h);
ArvoreRB* ProcuraMenor(ArvoreRB *atual);
int ConsultaArvore(ArvoreRB **raiz, int num);
ArvoreRB* RemoveNo(ArvoreRB *h, int valor);
int RemoveDaArvore(ArvoreRB **raiz, int valor);
void PreOrdem(ArvoreRB *raiz);
void EmOrdem(ArvoreRB *raiz);


