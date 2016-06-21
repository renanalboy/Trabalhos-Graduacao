/*
 * arvoreB.h
 *
 *  Created on: 31/05/2016
 *      Author: renan alboy
 */

#ifndef ARVOREAVL_H_
#define ARVOREAVL_H_

#include <stdio.h>
#include <stdlib.h>

struct NO{
	int info;
	int altura;
	struct NO *esq;
	struct NO *dir;
};

typedef struct NO* ArvAVL;


int altura_NO(struct NO* no);
int fatorBalanceamento_NO(struct NO* no);
int maior(int x, int y);
void rotacaoLL(ArvAVL *raiz);
void rotacaoRR(ArvAVL *raiz);
void rotacaoRL(ArvAVL *raiz);
void rotacaoLR(ArvAVL *raiz);
int insere_ArvAVL(ArvAVL *raiz, int valor);
int BuscaNoAVL(ArvAVL *r, int num)



#endif /* ARVOREAVL_H_ */
