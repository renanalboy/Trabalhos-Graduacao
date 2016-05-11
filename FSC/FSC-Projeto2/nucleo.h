/*
 * nucleo.h
 *
 *  Created on: 24/11/2014
 *      Author: renan
 */


typedef struct BCP{
	int PID;
	int Prioridade;

} bcp;

#ifndef NUCLEO_H_
#define NUCLEO_H_

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>
#include <semaphore.h>

//Protótipos
void executaNucleo();
int interruptControl();
void trataInterrupcao(int flag);
void sysCall();
void iniciaThreads();
void iniciaSemaforos();
void escalonar(int tempoExec);

// Declaração threads
pthread_t procI;
pthread_t procC;
pthread_t procF;
pthread_t semP;
pthread_t semV;
pthread_t ioR;
pthread_t ioF;
pthread_t memR;
pthread_t memF;
pthread_t fsR;
pthread_t fsF;
pthread_t escalonador;

// Atribuições
pthread_attr_t procI_ATTR;
pthread_attr_t procC_ATTR;
pthread_attr_t procF_ATTR;
pthread_attr_t semP_ATTR;
pthread_attr_t semV_ATTR;
pthread_attr_t ioR_ATTR;
pthread_attr_t ioF_ATTR;
pthread_attr_t memR_ATTR;
pthread_attr_t memF_ATTR;
pthread_attr_t fsR_ATTR;
pthread_attr_t fsF_ATTR;
pthread_attr_t escalonador_ATTR;

// Declaração funções para as threads
void processInterrupt();
void processCreate();
void processFinish();
void semaphoreP();
void semaphoreV();
void ioRequest();
void ioFinish();
void memLoadReq();
void memLoadFinish();
void fsRequest();
void fsFinish();

// Semaforos
sem_t semEscalonador;
sem_t semProcessos;



#endif /* NUCLEO_H_ */
