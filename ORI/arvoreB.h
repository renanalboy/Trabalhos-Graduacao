/*
 * arvoreB.h
 *
 *  Created on: 25/05/2016
 *      Author: fernanda
 */

#ifndef ARVOREB_H_
#define ARVOREB_H_

#define ordem 2
#define maximoDeChaves ordem-1
/*#define minimoDeChaves (int)ceil(ordem/2.0)-1*/ //arredonda float para cima
#define minimoDeChaves 0
#include <stdio.h>
#include <stdlib.h>
#include <time.h>



typedef struct Arquivo
{
int chave;
} Arquivo;

typedef struct _No
{
int numChaves;
Arquivo registros[maximoDeChaves];
struct _No *filhos[ordem];
} No;

typedef No *ArvoreB;
void inserirChave(ArvoreB arvore, Arquivo arq, No *subArvDir);
void verifica_Insercao(Arquivo arq, ArvoreB arvore, int *cresceu, Arquivo *regRetorno, ArvoreB *arvRetorno);
void percursoInOrdem(ArvoreB arvore);
void inserir_Elemento(Arquivo arq, ArvoreB *arvore);
ArvoreB buscaEmArvoreB (int chave, ArvoreB arvore);



#endif /* ARVOREB_H_ */
