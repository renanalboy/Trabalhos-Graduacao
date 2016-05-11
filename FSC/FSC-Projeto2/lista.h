/*
 * lista.h
 *
 *  Created on: 24/11/2014
 *      Author: renan
 */

typedef struct lista{
	int ident;
	int pri;
	struct lista *prox;
}Lista;

#ifndef LISTA_H_
#define LISTA_H_
#include <stdio.h>
#include <stdlib.h>

Lista* Criar(Lista*);
Lista* Insere(Lista* L,int ident, int pri);
Lista* Remove();
void Print(Lista* L);
int Empty(Lista* L);


#endif /* LISTA_H_ */
