#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct TipoNo *TipoApontador;
typedef struct Palavra{ char palavra[50];} Palavra;
typedef struct palavraHeap{ 
int qtd;
char palavra[50];} palavraHeap;

typedef struct arvoreInfo{
	int cmp;
	double tempo;	
}ArvoreInfo;

typedef struct TipoNo {
	Palavra p;
	int qtd;
	TipoApontador esq, dir;
} TipoNo;

typedef struct TipoHeap{
 palavraHeap *p;
 int tamanhoAtual;
 int tamanhoMaximo;
} TipoHeap;

void imprimeInfo(ArvoreInfo a){ 
printf("%d comparacoes\n%.4lf\n\n",a.cmp,a.tempo);
}
//Operacoes para arvore ABB
void inicializarABBeAVL(TipoApontador  *arvore,ArvoreInfo *ai) {
	 *arvore = NULL;
	 ai->cmp = 0;
	 ai->tempo = 0.0;
}

void inserirABB(Palavra x, TipoApontador *arvore,ArvoreInfo *ai){
	if (*arvore == NULL){
		*arvore = (TipoApontador) malloc(sizeof(TipoNo));
		(*arvore)->p = x;
		(*arvore)->qtd = 1;
		(*arvore)->esq = NULL;
		(*arvore)->dir = NULL;
		ai->cmp++;
		return;
	}else{
		ai->cmp++;
		int compare = strcmp(x.palavra,(*arvore)->p.palavra);
		if (compare != 0){
			inserirABB(x, (compare < 0)? &(*arvore)->esq :&(*arvore)->dir,ai);
		return;
		} else{
			(*arvore)->qtd++;
		}
	}
}

void imprimeABB(TipoApontador arv){
	if(arv!=NULL){
 		printf("%s: %d\n",arv->p.palavra,arv->qtd);
		imprimeABB(arv->esq);
		imprimeABB(arv->dir);
	}
}

Palavra removeEspeciais(char* name){
	Palavra p;
	int i = 0;
	for(i=0; i < strlen(name);i++){
	   	if(!(name[i]>=48 && name[i]<=57 || name[i]>=65 && name[i]<=90 || name[i]>=97 && name[i]<=122)){
			name[i] = ' ';
		}
	}
	strcpy(p.palavra, name);
	return p;
}

void finalizaTempo(ArvoreInfo *info){
	time_t fim = time(NULL); 
	info->tempo = difftime(fim, info->tempo);
	printf("\ntempo abb: %lf\ntempo compara:%d\n",info->tempo,info->cmp);
	//https://www.techiedelight.com/find-execution-time-c-program/
}

//Operacoes para arvore AVL
void imprimeArvores(ArvoreInfo abb, ArvoreInfo heap, ArvoreInfo avl){
	printf("heap:\n");
	imprimeInfo(heap);
	printf("abb:\n");
	imprimeInfo(abb);
	printf("avl:\n");
	imprimeInfo(avl);
	
	double menor = avl.tempo;
	
	if (abb.tempo < menor && abb.tempo < heap.tempo && menor < heap.tempo){
		//abb e o menor
	} else if (heap.tempo < menor && heap.tempo < abb.tempo && menor < abb.tempo){
		//heap e o menor
	} else if (menor < heap.tempo && menor < abb.tempo) {
		// avl e o  menor
	}else {
		//avl e o menor		
	}
}
 
void rotacaoSimplesEsq(TipoApontador *ppRaiz){
	 TipoApontador pAux;
	 pAux = (*ppRaiz)->dir;
	 (*ppRaiz)->dir = pAux->esq;
	 pAux->esq = (*ppRaiz);
	 (*ppRaiz) = pAux;
}

void rotacaoSimplesDir(TipoApontador *ppRaiz){
	 TipoApontador pAux;
	 pAux = (*ppRaiz)->esq;
	 (*ppRaiz)->esq = pAux->dir;
	 pAux->dir = (*ppRaiz);
	 (*ppRaiz) = pAux;
}

int fatorBalanceamento(TipoApontador pRaiz){
	 if (pRaiz == NULL) return 0;
	 return Altura(pRaiz->esq)- Altura(pRaiz->dir);
}

int Altura(TipoApontador pRaiz){
	 int iEsq,iDir;
	 if (pRaiz == NULL) return 0;
	 
	 iEsq = Altura(pRaiz->esq);
	 iDir = Altura(pRaiz->dir);
	 
	 if ( iEsq > iDir )	return iEsq + 1;
	 else return iDir + 1;
}
 
int rotacaoDuplaEsq(TipoApontador *ppRaiz){
	 int fbe = fatorBalanceamento((*ppRaiz)->esq );
	 if ( fbe > 0 ){
	 	rotacaoSimplesDir(ppRaiz);
	 	return 1;
	}
	 else if (fbe < 0 ){ 
	 	rotacaoSimplesEsq(&((*ppRaiz)->esq));
	 	rotacaoSimplesDir( ppRaiz );
	 	return 1;
	}
	 return 0;
}

int rotacaoDuplaDir(TipoApontador *ppRaiz){
	 int fbd = fatorBalanceamento( (*ppRaiz)->dir);
	 if ( fbd < 0 ){
		 rotacaoSimplesEsq(ppRaiz);
		 return 1;
	 }
	 else if (fbd > 0 ){ 
		 rotacaoSimplesDir( &((*ppRaiz)->dir) );
		 rotacaoSimplesEsq( ppRaiz );
		 return 1;
	}
	 return 0;
}

int balancaEsquerda(TipoApontador *ppRaiz){
	 int fbe = fatorBalanceamento((*ppRaiz)->esq);
	 if ( fbe > 0 ) {
	 rotacaoSimplesDir(ppRaiz);
	 return 1;
	 }
	 else if (fbe < 0 ){ 
	 rotacaoSimplesEsq( &((*ppRaiz)->esq) );
	 rotacaoSimplesDir(ppRaiz);
	 return 1;
	 }
	 return 0;
}

int balancaDireita(TipoApontador *ppRaiz){
	 int fbd = fatorBalanceamento( (*ppRaiz)->dir);
	 if ( fbd < 0 ){
	 rotacaoSimplesEsq(ppRaiz);
	 return 1;
	 }
	 else if (fbd > 0 ){ 
	 rotacaoSimplesDir( &((*ppRaiz)->dir) );
	 rotacaoSimplesEsq( ppRaiz );
	 return 1;
	 }
	 return 0;
}

int balanceamento(TipoApontador *ppRaiz){
	int fb = fatorBalanceamento(*ppRaiz);
	if ( fb > 1) return balancaEsquerda(ppRaiz);
	else if (fb < -1 ) return balancaDireita(ppRaiz);
	else return 0;
}

int insereAVL(TipoApontador *ppRaiz, ArvoreInfo *ai, Palavra x){ 
	 if (*ppRaiz == NULL){
		 *ppRaiz =(TipoApontador) malloc(sizeof(TipoNo));
		 (*ppRaiz)->p = x;
		 (*ppRaiz)->qtd = 1;
		 (*ppRaiz)->esq = NULL;
		 (*ppRaiz)->dir = NULL;
		 ai->cmp++;
		 return 1;
	 } else if (strcmp(x.palavra,(*ppRaiz)->p.palavra) > 0){
	 	 ai->cmp++;
	 	if(insereAVL(&(*ppRaiz)->esq,ai,x)){
		 ai->cmp++;
		if(balanceamento(ppRaiz)){
		 ai->cmp++;
		return 0;
		} else {
	 	 ai->cmp++;
		 return 1;
		 } 
	  }
	} else if(strcmp(x.palavra,(*ppRaiz)->p.palavra) < 0){
	 	ai->cmp++;
	 	if (insereAVL(&(*ppRaiz)->dir, ai,x)){
	 		ai->cmp++;
		 if (balanceamento(ppRaiz)){
		 	ai->cmp++;
		 	return 0;
		 } else return 1;
	  } else {
		ai->cmp++;
		return 0;
	 } 
	} else{
	(*ppRaiz)->qtd++;	
	return 0; 
	} 
}

void imprimeAVL(TipoApontador arv){
 if(arv!=NULL){
	imprimeAVL(arv->esq);
 	printf("%s: %d\n",arv->p.palavra,arv->qtd);
	imprimeAVL(arv->dir);
	}
}

//Auxiliares HEAP
int pai(int i){ return i/2;}
int filhoEsquerda(int i){ return 2*i;}
int filhoDireita(int i){ return 2*i + 1;}

//HEAP
void inicializarHeap(TipoHeap * h, int tamanhoMax){
 	h->p = (palavraHeap*) malloc(sizeof(palavraHeap)*(tamanhoMax+1));
	h->tamanhoAtual = 0;
	h->tamanhoMaximo = tamanhoMax;
}

int inserirHeap(TipoHeap * h, palavraHeap p, ArvoreInfo *ai){
 int i, c=0, equal=0;
 palavraHeap temp;
 while(equal == 0 && c < h->tamanhoAtual){
	ai->cmp + 2;
	if(strcmp(h->p[c].palavra, p.palavra) == 0){
		 equal= 1;
 		h->p[c].qtd++;
	 }
	 c++;
 }
 if(equal ==0){
 	ai->cmp++;
	 if (h->tamanhoAtual == h->tamanhoMaximo) return 0;
	 (h->tamanhoAtual)++;
	 i = h->tamanhoAtual;
	 h->p[i] = p;
	 h->p[i].qtd = 1;
	 
	 while ((i>1) &&  strcmp(h->p[pai(i)].palavra, h->p[i].palavra) > 0){
	 	ai->cmp++;
		 temp = h->p[i];
	 	h->p[i] = h->p[pai(i)];
	 	h->p[pai(i)] = temp;
	 	i = pai(i);
	}
 }
 return 1;
}

int main(){
    FILE *fp;
	char name[50];
	int count = 0, i=0;
	
	ArvoreInfo abb,avl,heap;
    TipoApontador arvoreBB,arvoreAVL,arvoreHEAP;
    inicializarABBeAVL(&arvoreBB,&abb);
	
	char file[60] = "Untitled.txt";
    //scanf("%s",file);
    
    fp = fopen(file, "r");
	abb.tempo = time(NULL);
    if(fp == NULL) {
		printf("Erro de leitura\n");
    	exit(1);
    }
    
    //ABB
    while(fscanf(fp, "%s", name ) != EOF ) {inserirABB(removeEspeciais(name),&arvoreBB,&abb);
	count++;}
    fclose(fp);
    finalizaTempo(&abb);
    imprimeABB(arvoreBB);
     
    //AVL
	fp = fopen(file, "r");
    avl.tempo = time(NULL);
	inicializarABBeAVL(&arvoreAVL,&avl);
	while(fscanf(fp, "%s", name ) != EOF ) {insereAVL(&arvoreAVL,&avl,removeEspeciais(name));}
    fclose(fp);
	finalizaTempo(&avl);
	imprimeAVL(arvoreAVL);
    
	//HEAP
	fp = fopen(file, "r");
    heap.tempo = time(NULL);
	inicializarHeap(&arvoreHEAP, count);
	while(fscanf(fp, "%s", name ) != EOF ) {insereAVL(&arvoreAVL,&avl,removeEspeciais(name));}
    fclose(fp);
	finalizaTempo(&avl);
	imprimeAVL(arvoreAVL);

    return 0;
}
