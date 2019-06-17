#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct TipoNoABB *TipoApontadorABB;
typedef struct Palavra{ char palavra[50];} Palavra;
typedef struct arvoreInfo{
	int cmp;
	double tempo;	
}ArvoreInfo;

typedef struct TipoNoABB {
	Palavra p;
	int qtd;
	TipoApontadorABB esq, dir;
} TipoNoABB;

void inicializarABB(TipoApontadorABB  *arvore,ArvoreInfo *ai) {
	 *arvore = NULL;
	 ai->cmp = 0;
	 ai->tempo = 0.0;
}

void inserirABB(Palavra x, TipoApontadorABB *arvore,ArvoreInfo *ai){
	if (*arvore == NULL){
		*arvore = (TipoApontadorABB) malloc(sizeof(TipoNoABB));
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

void imprimeABB(TipoApontadorABB arv){
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

 
void finalizaTempo(time_t inicio){
	time_t fim = time(NULL); 
	printf("\n Tempo do programa %f segundos", difftime(fim, inicio));
	//https://www.techiedelight.com/find-execution-time-c-program/
}

void imprimeArvores(ArvoreInfo abb, ArvoreInfo heap, ArvoreInfo avl){
	printf("heap:\n");
	imprimeInfo(heap);
	printf("abb:\n");
	imprimeInfo(avl);
	printf("avl:\n");
	imprimeInfo(avl);
	double menor = avl.tempo;
	if (abb.tempo < menor && abb.tempo < heap.tempo && menor < heap.tempo){
		
	} else if(heap.tempo < menor && heap.tempo < abb.tempo && menor < abb.tempo){
		//heap é menor
	} else {
		// avl é menor
	}
}

void imprimeInfo(ArvoreInfo a){
		printf("heap:\n%d comparacoes\n%.4lf\n\n",a.cmp,a.tempo);
}
  
int main(){
    FILE *fp;
	char name[50];
	int count = 0, i=0;
	
	char file[60] = "Untitled.txt";
    //scanf("%s",file);
    fp = fopen(file, "r");
	time_t inicio = time(NULL);
    
    if(fp == NULL) {
        printf("Erro de leitura\n");
        exit(1);
    }
    
    ArvoreInfo abb;
    TipoApontadorABB arvoreBB;
    inicializarABB(&arvoreBB,&abb);
    
    while(fscanf(fp, "%s", name ) != EOF ) {inserirABB(removeEspeciais(name),&arvoreBB,&abb);}
    fclose(fp);
    imprimeABB(arvoreBB);
    finalizaTempo(inicio);
    
    return 0;
}
