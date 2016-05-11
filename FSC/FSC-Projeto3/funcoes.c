/*
 * funcoes.c
 *
 *  Created on: 13/01/2015
 *      Author: renan
 */

#include "funcoes.h"

int ACK = 0;
int NOACK = 0;

//Sortei o tempo T de resposta
int sorteiTempoResposta (){
	int num;
	srand( (unsigned) time(NULL) );
	num = (rand()%16);
	return num;
}

//referente ao valor de k e L
float enviaMenssagem (){
	float num;
	srand( (unsigned) time(NULL) );
	num = (rand()%100);
	num = num/100;
	return num;
}


// Executa as comparações, trata os semaforos e chama a thread que recebe o pacote
void moduloEnvia(){

	int packs, T;

	printf("\n\n\n");

	printf("Numero de pacotes a ser enviados:\n");
	scanf("%d", &packs);
	printf("\n");

	sem_post(&envia);

	while(packs>0){

		sem_wait(&envia);

		sleep(2);
		T=sorteiTempoResposta();

		printf("Numero sorteado: %d\n",T);

		sem_post(&recebe);

		pthread_create(&recebeP, &recebeP_ATTR,(void*)moduloRecebe,NULL);

		pthread_join(recebeP, NULL);

		sem_wait(&recebe);

		if(T > 10){
			sleep(10);
			printf("Nao houve resposta... reenviando.\n");
		}

		if(ACK == 1 && T < 11){
			sleep(T);
			printf("Alterado valor do ACK para 1.\n");
			printf("Pacote %d enviado com sucesso.\n", packs);
			packs --;
		}
		if(NOACK == 1 && T < 11){
			printf("Alterado valor do NOACK para 1.\n");
			sleep(T);
			printf("O pacote nao foi recebido.\n");
		}

		ACK=0;
		NOACK=0;

		printf("Restam %d pacotes para serem enviados.\n ", packs);
		printf("\n\n");

		sem_post(&envia);
	}

	printf("Todos os pacotes foram enviados.\n\n\n");

	if(packs == 0){
		printf("A qunatidade de pacote desejada foie nviada com sucesso!");
	}
}

void moduloRecebe(){

	float K = 0.6;
	float L =0.3;
	float sorteio;

	sorteio=enviaMenssagem();

	printf("Valor sorteado: %f \n", sorteio);
	//caso valor seja maior do que K
	if(sorteio > K){
		ACK =1;
	}
	//caso valor esteja entre L e K
	if(sorteio > L && sorteio <= K){
		NOACK = 1;
	}
}





