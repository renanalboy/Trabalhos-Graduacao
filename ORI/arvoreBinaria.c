#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct NoBinaria{
	int num;
	struct NoBinaria* dir;
	struct NoBinaria* esq;
} NoBinaria;

typedef NoBinaria *ArvoreBinaria;

int nivelBuscaBinaria=0;

//Insere na árvores com recursão
void InsereNo(ArvoreBinaria r, int num){

	if(!r){
		NoBinaria *no;
		no = (NoBinaria*)malloc(sizeof(NoBinaria));
    	no->esq = NULL;
    	no->dir = NULL;
    	no->num = num;

	}
	else{
		if(num < r->num){
			//percorre sub-árvore da esquerda
			InsereNo(r->esq, num);
		}
		if(num > r->num){
			//percorre sub-árvore da direita
			InsereNo(r->dir, num);
		}
	}
}

ArvoreBinaria inserir (ArvoreBinaria raiz, int info)
{
	if (!raiz) {
		NoBinaria *raiz;
		raiz = (NoBinaria*)malloc(sizeof(NoBinaria));
		raiz->num = info;
		raiz->esq = NULL;
		raiz->dir = NULL;

	return raiz;
	}
	else
		if (info > raiz->num)
			raiz->dir = inserir (raiz->dir, info);
		else
			raiz->esq = inserir (raiz->esq, info);

	return raiz;
}

ArvoreBinaria procurar (ArvoreBinaria raiz, int info){
	puts("Entrada binaria");
	if (!raiz){
		puts("Entrada binaria");
		FILE *arq;
		char infotexto[100];
		char name[10];
		sprintf(name, "%d", info);
		arq = fopen(strcat(name,".txt"), "r");
		while( (fgets(infotexto, sizeof(infotexto), arq)!=NULL)){
			printf("%s",infotexto);
		}
		fclose(arq);
		printf("%d",nivelBuscaBinaria);
		nivelBuscaBinaria=0;
		return NULL;
	}

	if (info > raiz->num){
		nivelBuscaBinaria++;
		return procurar(raiz->dir, info);
	}
	else{
		nivelBuscaBinaria++;
		return procurar (raiz->esq, info);
	}



	return NULL;
}


int BuscaNo(ArvoreBinaria r, int num){
	puts("Entrada binaria");
	if(r == NULL){
		puts("Entrada binaria");
		return 0;
	}
	else{
		if(r->num == num){
			puts("Entrada binaria");
			FILE *arq;
			char info[100];
			char name[10];
			sprintf(name, "%d", num);
			arq = fopen(strcat(name,".txt"), "r");
			while( (fgets(info, sizeof(info), arq)!=NULL)){
						printf("%s",info);
			}
			fclose(arq);
			printf("%d",nivelBuscaBinaria);
			nivelBuscaBinaria=0;
			return num;
		}
		else{
			if(r-> num > num){
				puts("ch1");
				nivelBuscaBinaria++;
				BuscaNo(r->dir, num);
			}
			if(r->num < num){
				puts("ch2");
				nivelBuscaBinaria++;
				BuscaNo(r->esq, num);
			}
		}
	}
	return num;
}
