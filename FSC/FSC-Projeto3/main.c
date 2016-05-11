/*
 * main.c
 *
 *  Created on: 13/01/2015
 *      Author: renan
 */

#include "funcoes.h"

void main(){

	printf("##########################################################################\n");
	printf("#   Alunos:                                                              #\n");
	printf("#      Chen Yuxuan                                                       #\n");
	printf("#      Renan Galeane Alboy                                               #\n");
	printf("#                                                                        #\n");
	printf("#                                                                        #\n");
	printf("#           Trabalho 3 FSC                                               #\n");
	printf("#                                                                        #\n");
	printf("##########################################################################\n");

	pthread_create(&enviaP, &enviaP_ATTR,(void*)moduloEnvia, NULL);

	pthread_join(enviaP, NULL );

}
