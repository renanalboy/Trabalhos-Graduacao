/*
 * lista.c
 *
 *  Created on: 24/11/2014
 *      Author: renan
 */


#include "lista.h"



Lista* Criar(Lista* L){
	L=NULL;
	return L;
}

Lista* Insere(Lista* L,int ident,int pri){
	 Lista *p;
	 Lista *novo = (Lista*)malloc(sizeof(Lista));
	novo->ident = ident;
	novo->pri = pri;
	novo->prox = NULL;
	if(L==NULL){
		L = novo;
	}
	else{
		p=L;
		while(p->prox){
			p = p->prox;
		}
		p->prox = novo;
	}
	return L;

}

Lista* Remove(Lista* L){
	Lista *q = NULL;
	Lista *p;
	p=L;
	if(p->prox){
		q = p;
		L = p->prox;
	}
	else{
		L=NULL;
	}
	free(q);
	return L;

}

void Print(Lista* L){
	Lista *p;
	p=L;
	puts("Imprimindo Lista: ");
	while(p){
		printf("PID = %d ", p->ident);
		printf("Prioridade = %d \n",p->pri);
		p = p->prox;
	}

}

int Empty(Lista* L){
	if(L==NULL) return 0;
	else
		return 0;
}
