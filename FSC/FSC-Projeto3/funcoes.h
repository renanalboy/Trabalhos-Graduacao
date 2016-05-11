/*
 * funcoes.h
 *
 *  Created on: 13/01/2015
 *      Author: renan
 */

#ifndef FUNCOES_H_
#define FUNCOES_H_
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<pthread.h>
#include<semaphore.h>
#include<unistd.h>

//Funções
int sorteiTempoResposta ();
float enviaMenssagem ();
void stopWait(int packs);
void initThread();
void initSemaforo();
void moduloEnvia();
void moduloRecebe();

//Declaração das threads
pthread_t enviaP;
pthread_t recebeP;

pthread_attr_t enviaP_ATTR;
pthread_attr_t recebeP_ATTR;

//Declaração dos semaforos
sem_t envia;
sem_t recebe;


#endif /* FUNCOES_H_ */
