#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct TipoNo *TipoApontador;
typedef struct Palavra{ char palavra[50];} Palavra;
typedef struct arvoreInfo{
	int cmp;
	double tempo;	
}ArvoreInfo;

typedef struct TipoNo {
	Palavra p;
	int qtd;
	TipoApontador esq, dir;
} TipoNo;

void imprimeInfo(ArvoreInfo a){ 
printf("%d comparacoes\n%.4lf\n\n",a.cmp,a.tempo);
}

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

void finalizaTempo(time_t inicio, ArvoreInfo *info){
	time_t fim = time(NULL); 
	info->tempo = difftime(fim, inicio);
	printf("\ntempo abb: %lf\ntempo compara:%d",info->tempo,info->cmp);
	//https://www.techiedelight.com/find-execution-time-c-program/
}

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
	 pAux = (*ppRaiz)->pDir;
	 (*ppRaiz)->pDir = pAux->pEsq;
	 pAux->pEsq = (*ppRaiz);
	 (*ppRaiz) = pAux;
}

void rotacaoSimplesDir(TipoApontador *ppRaiz){
	 TipoApontador pAux;
	 pAux = (*ppRaiz)->pEsq;
	 (*ppRaiz)->pEsq = pAux->pDir;
	 pAux->pDir = (*ppRaiz);
	 (*ppRaiz) = pAux;
}
  
int rotacaoDuplaEsq(TipoApontador *ppRaiz){
	 int fbe = FB ( (*ppRaiz)->pEsq );
	 if ( fbe > 0 ){
	 	rotacaoSimplesDir(ppRaiz);
	 	return 1;
	}
	 else if (fbe < 0 ){ 
	 	rotacaoSimplesEsq( &((*ppRaiz)->pEsq));
	 	rotacaoSimplesDir( ppRaiz );
	 	return 1;
	}
	 return 0;
}
int BalancaDireita(TipoApontador *ppRaiz){
	 int fbd = FB( (*ppRaiz)->pDir);
	 if ( fbd < 0 ){
	 rotacaoSimplesEsq(ppRaiz);
	 return 1;
	 }
	 else if (fbd > 0 ){ 
	 rotacaoSimplesDir( &((*ppRaiz)->pDir) );
	 rotacaoSimplesEsq( ppRaiz );
	 return 1;
	 }
	 return 0;
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
	time_t inicio = time(NULL);
    if(fp == NULL) {
		printf("Erro de leitura\n");
    	exit(1);
    }
    
    while(fscanf(fp, "%s", name ) != EOF ) {inserirABB(removeEspeciais(name),&arvoreBB,&abb);}
    fclose(fp);
    finalizaTempo(inicio, &abb);
     
	fp = fopen(file, "r");
    inicializarABBeAVL(&arvoreAVL,&avl);
    avl.tempo = time(NULL);
//	while(fscanf(fp, "%s", name ) != EOF ) {inserirHeap(removeEspeciais(name),&arvoreAVL,&avl);}
    fclose(fp);
    
	//imprimeABB(arvoreBB);
    
    return 0;
}
