#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <time.h>

typedef struct TipoNo *TipoApontador;
typedef struct Palavra{ char palavra[50];} Palavra;
typedef struct palavraHeap{ 
	int qtd;
	char palavra[50];
	} palavraHeap;

typedef struct arvoreInfo{
	int cmp;
	struct timeval tempo;
	long final;
	long micros;	
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
printf("%d comparacoes\n%d segundos\n\n",a.cmp,a.final);
}
//Operacoes para arvore ABB
void inicializarABBeAVL(TipoApontador  *arvore,ArvoreInfo *ai) {
	 *arvore = NULL;
	 ai->cmp = 0;
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
	struct timeval fim;
	gettimeofday(&fim, NULL);
	info->final = (fim.tv_sec - info->tempo.tv_sec);
	info->micros = ((info->final * 1000000) + fim.tv_usec) - (info->tempo.tv_usec);
	//https://www.techiedelight.com/find-execution-time-c-program/
}

//Operacoes para arvore AVL

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
void imprimeHeap(TipoHeap h){
if(h.tamanhoAtual > 0){
	int i = h.tamanhoAtual;
	while( i > 1){
 		printf("%s:%d\n", h.p[i].palavra,h.p[i].qtd);
		i--;
	}
}

}

void inicializarHeap(TipoHeap * h, int tamanhoMax, ArvoreInfo * ai){
 	h->p = (palavraHeap*) malloc(sizeof(palavraHeap)*(tamanhoMax+1));
	h->tamanhoAtual = 0;
	h->tamanhoMaximo = tamanhoMax;
	ai->cmp = 0;
	ai->final =0;
}

int inserirHeap(TipoHeap * h, palavraHeap p, ArvoreInfo *ai){
 int i, c=0, equal=0;
 palavraHeap temp;
 while(equal == 0 && c < h->tamanhoAtual){
	 ai->cmp++;
	if(strcmp(h->p[c].palavra, p.palavra) == 0){
		 equal= 1;
 		h->p[c].qtd++;
	 }
	 c++;
 }
 if(equal ==0){
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

void imprimeArvores(ArvoreInfo abb, ArvoreInfo heap, ArvoreInfo avl, TipoApontador aabb, TipoApontador aavl, TipoHeap aheap){
	printf("heap:\n");
	imprimeInfo(heap);
	printf("abb:\n");
	imprimeInfo(abb);
	printf("avl:\n");
	imprimeInfo(avl);
	
	long menor = avl.micros;
		if(abb.micros > heap.micros && heap.micros < menor){	menor = heap.micros;} else if(abb.micros < heap.micros && menor > abb.micros ) {menor=abb.micros;}
		if(menor > abb.micros){menor = abb.micros;} 
		if(menor > heap.micros){	menor = heap.micros;} 
		//printf("sai do if com menor == %d\navl:%d\nheap:%d\nabb:%d\n",menor,avl.micros,heap.micros,abb.micros);
		if(menor == abb.micros){
		imprimeABB(aabb);
		}	else if(menor == heap.micros){
		imprimeHeap(aheap);
		}else{
		imprimeAVL(aavl);
	
		}
		//printf("\n abb menor com %d milesegundos",abb.micros);
		//printf("\n avl menor com %f milesegundos",avl.micros);
		//printf("\n heap menor com %d milesegundos",heap.micros);		
}
 

int main(){
    FILE *fp;
	char name[50],file[60];
	int count = 0, i=0;
	
	ArvoreInfo abb,avl,heap;
    TipoApontador arvoreBB,arvoreAVL;
	TipoHeap arvoreHEAP;
    inicializarABBeAVL(&arvoreBB,&abb);
	
    scanf("%s",file);
    
    fp = fopen(file, "r");
	gettimeofday(&abb.tempo, NULL);
	sleep(1);
		
    if(fp == NULL) {
		printf("Erro de leitura\n");
    	exit(1);
    }
    
    //ABB
    while(fscanf(fp, "%s", name ) != EOF ) {inserirABB(removeEspeciais(name),&arvoreBB,&abb);
	count++;}
    fclose(fp);
    finalizaTempo(&abb);
    //imprimeABB(arvoreBB);
     
    //AVL
	fp = fopen(file, "r");
     gettimeofday(&avl.tempo, NULL);
    sleep(1);
	inicializarABBeAVL(&arvoreAVL,&avl);
	while(fscanf(fp, "%s", name ) != EOF ) {insereAVL(&arvoreAVL,&avl,removeEspeciais(name));}
    fclose(fp);
	finalizaTempo(&avl);
	//imprimeAVL(arvoreAVL);
    
	//HEAP
	fp = fopen(file, "r");
	palavraHeap p;
	Palavra pse;
	inicializarHeap(&arvoreHEAP, count,&heap);
    gettimeofday(&heap.tempo , NULL);
    sleep(1);
	while(fscanf(fp, "%s", name ) != EOF ) {
		pse = removeEspeciais(name);
	 	strcpy(p.palavra, pse.palavra);
		inserirHeap(&arvoreHEAP,p,&heap);
	}
    fclose(fp);
	finalizaTempo(&heap);
	imprimeArvores(abb,heap,avl,arvoreBB,arvoreAVL,arvoreHEAP);

    return 0;
}
