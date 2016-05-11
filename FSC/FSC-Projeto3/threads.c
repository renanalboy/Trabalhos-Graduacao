/*
 * threads.c
 *
 *  Created on: 14/01/2015
 *      Author: renan
 */

#include "funcoes.h"
//Declaração threads
void initThread(){

	pthread_attr_init(&enviaP);
	pthread_attr_init(&recebeP);

	pthread_attr_setscope(&enviaP, PTHREAD_SCOPE_SYSTEM);
	pthread_attr_setscope(&recebeP, PTHREAD_SCOPE_SYSTEM);
}

void initSemaforo(){
	sem_init(&envia,1,1);
	sem_init(&recebe,1,0);
}

