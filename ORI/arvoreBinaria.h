/*
 * arvoreBinaria.h
 *
 *  Created on: 25/05/2016
 *      Author: fernanda
 */

#ifndef ARVOREBINARIA_H_
#define ARVOREBINARIA_H_
#include <stdio.h>
#include <stdlib.h>



typedef struct NoBinaria{
	int num;
	struct NoBinaria* dir;
	struct NoBinaria* esq;
} NoBinaria;

typedef NoBinaria *ArvoreBinaria;

void InsereNo(ArvoreBinaria r, int num);
int BuscaNo(ArvoreBinaria r, int num);
ArvoreBinaria procurar (ArvoreBinaria raiz, int info);
ArvoreBinaria inserir (ArvoreBinaria raiz, int info);

#endif /* ARVOREBINARIA_H_ */
