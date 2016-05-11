/*
 * nucleo.c
 *
 *  Created on: 24\11\2014
 *      Author: renan
 */

#include "nucleo.h"
#include "lista.h"

int flag;
char nomeArquivo[10];
struct lista *Prontos;
struct BCP Dados;
struct lista *Fila1;
struct lista *Fila2;
struct lista *Fila3;
struct lista *Fila4;
struct lista *Fila5;
struct lista *emExecucao;
struct lista *emEspera;
struct lista *terminados;
char listaSemaforos[10];
int executando = 0;
char sem;

void executaNucleo() {

	Prontos = Criar(Prontos);
	Fila1 = Criar(Fila1);
	Fila2 = Criar(Fila2);
	Fila3 = Criar(Fila3);
	Fila4 = Criar(Fila4);
	Fila5 = Criar(Fila5);
	emExecucao = Criar(emExecucao);
	emEspera = Criar(emEspera);
	terminados = Criar(terminados);
	listaSemaforos[0] = '\0';

	iniciaThreads();
	iniciaSemaforos();
	flag = interruptControl();
	trataInterrupcao(flag);

}

//Função para inicializar as threads
void iniciaThreads() {

	puts("Preparando para iniciar threads ...");
	puts("Iniciando das threads ...");

	pthread_attr_init(&procI_ATTR);
	pthread_attr_init(&procC_ATTR);
	pthread_attr_init(&procF_ATTR);
	pthread_attr_init(&semP_ATTR);
	pthread_attr_init(&semV_ATTR);
	pthread_attr_init(&ioR_ATTR);
	pthread_attr_init(&ioF_ATTR);
	pthread_attr_init(&memR_ATTR);
	pthread_attr_init(&memF_ATTR);
	pthread_attr_init(&fsR_ATTR);
	pthread_attr_init(&fsF_ATTR);
	pthread_attr_init(&escalonador_ATTR);

	pthread_attr_setscope(&procI_ATTR, PTHREAD_SCOPE_SYSTEM);
	pthread_attr_setscope(&procC_ATTR, PTHREAD_SCOPE_SYSTEM);
	pthread_attr_setscope(&procF_ATTR, PTHREAD_SCOPE_SYSTEM);
	pthread_attr_setscope(&semP_ATTR, PTHREAD_SCOPE_SYSTEM);
	pthread_attr_setscope(&semV_ATTR, PTHREAD_SCOPE_SYSTEM);
	pthread_attr_setscope(&ioR_ATTR, PTHREAD_SCOPE_SYSTEM);
	pthread_attr_setscope(&ioF_ATTR, PTHREAD_SCOPE_SYSTEM);
	pthread_attr_setscope(&memR_ATTR, PTHREAD_SCOPE_SYSTEM);
	pthread_attr_setscope(&memF_ATTR, PTHREAD_SCOPE_SYSTEM);
	pthread_attr_setscope(&fsR_ATTR, PTHREAD_SCOPE_SYSTEM);
	pthread_attr_setscope(&fsF_ATTR, PTHREAD_SCOPE_SYSTEM);
	pthread_attr_setscope(&escalonador_ATTR, PTHREAD_SCOPE_SYSTEM);
}

//Inicialização dos semáforos
void iniciaSemaforos(){

	sem_init(&semEscalonador, 1, 1);
	sem_init(&semProcessos, 1, 1);
}

// Gerencia interrutControl, resulta em 0 caso não aja processos em execução
int interruptControl(){

	int proc;

	if(executando==0){
		proc=0;
	}

	return proc;

}

void trataInterrupcao(int flag){

	switch(flag){

		case 0 :
			printf("Chamando sysCall ...\n");
			printf("Nome do arquivo:\n");
			scanf("%s", nomeArquivo);
			sysCall(nomeArquivo);
			break;

		case 1 :
			printf("Processo interronpido ..\n");
			pthread_create(&procI, &procI_ATTR,(void*) &processInterrupt, NULL);
			pthread_join(procI, NULL);
			break;

		case 2 :
			printf("Criando processo ...\n");
			pthread_create(&procC, &procC_ATTR, (void*) &processCreate, NULL);
			pthread_join(procC, NULL);
			break;

		case 3 :
			printf("Processo finalizado ...\n");
			pthread_create(&procF, &procF_ATTR, (void*) &processFinish, NULL);
			pthread_join(procF, NULL);
			break;

		case 4 :
			printf("Realizando E/S ...\n");
			pthread_create(&ioR, &ioR_ATTR, (void*) &ioRequest, NULL);
			pthread_join(ioR, NULL);
			break;

		case 5 :
			printf("Finalizando E/S...\n");
			pthread_create(&ioF, &ioF_ATTR, (void*) &ioFinish, NULL);
			pthread_join(ioF, NULL);
			break;

		case 6 :
			printf("Carregando na memoria ... \n");
			pthread_create(&memR, &memR_ATTR, (void*) &memLoadReq, NULL);
			pthread_join(memR, NULL);
			break;

		case 7 :
			printf("Fim de carregamento ... \n");
			pthread_create(&memF, &memF_ATTR, (void*) &memLoadFinish, NULL);
			pthread_join(memF, NULL);
			break;

		case 8 :
			printf("Operação no sistema de arquivos ...\n");
			pthread_create(&fsR, &fsR_ATTR,(void*) &fsRequest, NULL);
			pthread_join(fsR,NULL);
			break;

		case 9 :
			printf("Final de operação no sistema de arquivos ...\n");
			pthread_create(&fsF, &fsF_ATTR,(void*) &fsFinish, NULL);
			pthread_join(fsF,NULL);
			break;

		case 10:
			printf("Bloqueio de processo ...\n");
			pthread_create(&semP, &semP_ATTR,(void*) &semaphoreP, NULL);
			pthread_join(semP,NULL);
			break;

		case 11:
			printf(" Desbloqueio de processo ...\n");
			pthread_create(&semV, &semV_ATTR,(void*) &semaphoreV, NULL);
			pthread_join(semV,NULL);
			break;
	}//fim switch
}

void sysCall(char* arquivo){

	FILE* arq;
	char url[100], info[100], valor[10];

	int num=0, i=0, tempoExec=0, id, pri, tam, converte;
	char nome[10], listaSem[10];

	if(arq == NULL){
		printf("Erro ao abrir o arquivo\n");
	}else{
		printf("Leitura do arquivo ... \n \n");
		strcpy(url,arquivo);
		printf("%s \n",url);
		//Abertura do arquivo para leitura
		arq = fopen(url, "r");
		printf("Executando a leitura ... \n");
	}

	//Leitura do cabeçalho do arquivo sintético
	printf("Executando leitura de cabecalho ...\n");
			while( (fgets(info, sizeof(info), arq) != NULL)){
				if(i == 0) {
					strcpy(nome,info);
					printf("%s \n",nome);
				}
				if(i == 1){
					id = atoi(info);
					Dados.PID = id;
					printf("%d \n",Dados.PID);
				}
				if(i==2){
					pri = atoi(info);
					Dados.Prioridade = pri;
					printf("%d \n",Dados.Prioridade);
				}
				if(i==3){
					tam = atoi(info);
					printf("%d \n",tam);
				}
				if(i==4){
					strcpy(listaSem,info);
					printf("%s \n",listaSem);
				}
				if(i==5) break;
				i++;

			}
			trataInterrupcao(2);

			//lê o arquivo até o final e exibe na tela
			printf("Executando leitura de instrucoes\n\n");
			while( (fgets(info, sizeof(info), arq) != NULL)){
			if(info[0]== 'e' && info[1]== 'x'){
				i=5;
				while(info[i] != '\0'){
					valor[num]=info[i];
					i++;
					num++;
				}
				valor[num] = '\0';
				converte = atoi(valor);
				printf("Executar por %d ut \n",converte);
				tempoExec = tempoExec+converte;

				num=0;
				i=0;

			}else{
				if(info[0] == 'r' && info[1] == 'e'){

					i=5;
					while(info[i] != '\0'){
						valor[num]=info[i];
						i++;
						num++;
					}
					valor[num] = '\0';
					converte = atoi(valor);
					printf("Ler o disco na trilha %d \n",converte);

					num=0;
					i=0;
				}else{
					if(info[0]=='w' && info[1]=='r'){

					i=6;
					while(info[i] != '\0'){
						valor[num]=info[i];
						i++;
						num++;
					}
					valor[num] = '\0';
					converte = atoi(valor);
					printf("Escrever na trilha %d \n",converte);

					num=0;
					i=0;
					}else {
						if(info[0]=='P' && info[1]=='('){
						sem = info[2];
						printf("\n");
						printf("Bloquear Semaforo %c \n",sem);
						trataInterrupcao(10);
						}else{
							if(info[0]=='V' && info[1]=='('){
							sem = info[2];

							printf("Liberar Semaforo %c \n",sem);
							trataInterrupcao(11);
							}else{
								if(info[0]=='p' && info[1]=='r'){

									i=6;
									while(info[i] != '\0'){
										valor[num]=info[i];
										i++;
										num++;
									}
								valor[num] = '\0';
								converte = atoi(valor);
								printf("Imprime por %d ut \n",converte);

								num=0;
								i=0;
								}else{
									if(info[0]=='c' && info[1]=='a'){

										i=6;
										while(info[i] != ')'){
											valor[num]=info[i];
											i++;
											num++;
										}
										valor[num] = '\0';

										printf("Chama processo: %s \n",valor);


										sysCall(valor);

										num=0;
										i=0;
									}
								}
							}
						}
					}
				}
			}

			}//finaliza leitura das linhas


			fclose(arq);
			pthread_create(&escalonador, &escalonador_ATTR,(void*) &escalonar,(void*)(unsigned long long) tempoExec);
			pthread_join(escalonador,NULL);
			trataInterrupcao(0);
}

void processInterrupt(){

	printf("Interrupcao pelo fim do quantum ... retornando processo a fila ...\n\n");
	switch(Dados.Prioridade){
		case 1:
			Fila1 = Insere(Fila1,Dados.PID,Dados.Prioridade); break;

		case 2:
			Fila2 = Insere(Fila2,Dados.PID,Dados.Prioridade); break;

		case 3:
			Fila3 = Insere(Fila3,Dados.PID,Dados.Prioridade); break;

		case 4:
			Fila4 = Insere(Fila4,Dados.PID,Dados.Prioridade); break;

		case 5:
			Fila5 = Insere(Fila5,Dados.PID,Dados.Prioridade); break;
	}
}

void processCreate(){

	printf("Criando processos e adicionando na lista de prontos:\n");
	Prontos = Insere(Prontos,Dados.PID,Dados.Prioridade);
	printf("Processos na lista de prontos:\n");
	Print(Prontos);
	puts("Colocando o processo na fila de acordo com suas prioridades ... \n ");

	switch (Dados.Prioridade){
		case 1:
			Fila1 = Insere(Fila1,Dados.PID,Dados.Prioridade);
			printf("Inserido na fila 1 \n");
			break;

		case 2:
			Fila2 = Insere(Fila2,Dados.PID,Dados.Prioridade);
			printf("Inserido na fila 2 \n");
			break;

		case 3:
			Fila3 = Insere(Fila3,Dados.PID,Dados.Prioridade);
			printf("Inserido na fila 3 \n");
			break;

		case 4:
			Fila4 = Insere(Fila4,Dados.PID,Dados.Prioridade);
			printf("Inserido na fila 4");
			break;

		case 5:
			Fila5 = Insere(Fila5,Dados.PID,Dados.Prioridade);
			break;
	}

	sem_post(&semEscalonador);
}


void processFinish(){

	sem_wait(&semEscalonador);
	puts("Processo Terminou");
	puts("Adicionando processos a lista de terminados ...");
	Prontos = Remove(Prontos);
	terminados = Insere(terminados,Dados.PID,Dados.Prioridade);
}


void semaphoreP(){

	int i=0, achou=0;

	printf("Verificação dos semaforos ....\n");
	sem_wait(&semProcessos);

	while(listaSemaforos[i]!='\0'){
		if(listaSemaforos[i]==sem){
			achou = 1;
		}
		i++;
	}

	if(achou == 1){
		printf("Processo em espera ... \n");
		emEspera = Insere(emEspera,Dados.PID,Dados.Prioridade);
	}else{
		listaSemaforos[i] = sem;
		listaSemaforos[i+1]='\0';
		printf("O semaforo %c foi bloqueado ... \n", sem);
	}

	sem_post(&semProcessos);
}

void semaphoreV(){

	int i=0;

	printf("Verificando semaforos ...\n");
	sem_wait(&semProcessos);

	while(listaSemaforos[i]!=sem){
		i++;
	}

	listaSemaforos[i] = ' ';
	printf("O semaforo %c foi liberado ...\n", sem);
	sem_post(&semProcessos);
}

void ioRequest(){
	//Função ainda não implementadas neste trabalho
}
void ioFinish(){
	//Função ainda não implementadas neste trabalho
}
void memLoadReq(){
	//Função ainda não implementadas neste trabalho
}
void memLoadFinish(){
	//Função ainda não implementadas neste trabalho
}
void fsRequest(){
	//Função ainda não implementadas neste trabalho
}
void fsFinish(){
	//Função ainda não implementadas neste trabalho
}

void escalonar(int tempoExec){

	int i=0;

	sem_wait(&semEscalonador);
	if(tempoExec > 0){
		printf("#-----------------------------------------------------------------------------------------#\n");
		printf("#-----------------------------------------------------------------------------------------#\n\n");
		if(executando == 0){
			printf("Iniciando execução \n");
			executando = 1;

			switch(Dados.Prioridade){
				case 1:
					Fila1 = Remove(Fila1);
					emExecucao = Insere(emExecucao,Dados.PID,Dados.Prioridade);

					printf("Executando processo por 100 ut \n");
					for(i=0;i<3;i++){
						printf("Executando processo ... \n");
						sleep(2);
					}
					tempoExec = tempoExec - 100;
					emExecucao = Remove(emExecucao);

					if(tempoExec > 0){
						trataInterrupcao(1);
					}else{
						trataInterrupcao(3);
					}

					break;

				case 2:
					Fila2 = Remove(Fila2);
					emExecucao = Insere(emExecucao,Dados.PID,Dados.Prioridade);

					printf("Executando processo por 200 ut \n");
					for(i=0;i<3;i++){
						printf("Executando processo ... \n");
						sleep(2);
					}
					tempoExec = tempoExec - 200;
					emExecucao = Remove(emExecucao);

					if(tempoExec > 0){
						trataInterrupcao(1);
					}else{
						trataInterrupcao(3);
				    }

					break;

				case 3:
					Fila3 = Remove(Fila3);
					emExecucao = Insere(emExecucao,Dados.PID,Dados.Prioridade);

					printf("Executando processo por 400 ut \n");
					for(i=0;i<3;i++){
						printf("Executando processo ... \n");
						sleep(2);
					}
					tempoExec = tempoExec - 400;
					emExecucao = Remove(emExecucao);

					if(tempoExec > 0){
						trataInterrupcao(1);
					}else{
						trataInterrupcao(3);
					}

					break;

				case 4:
					Fila2 = Remove(Fila2);
					emExecucao = Insere(emExecucao,Dados.PID,Dados.Prioridade);

					printf("Executando processo por 600 ut \n");
					for(i=0;i<3;i++){
						printf("Executando processo ... \n");
						sleep(2);
					}
					tempoExec = tempoExec - 600;
					emExecucao = Remove(emExecucao);

					if(tempoExec > 0){
						trataInterrupcao(1);
					}else{
						trataInterrupcao(3);
					}

					break;

				case 5:
					Fila2 = Remove(Fila2);
					emExecucao = Insere(emExecucao,Dados.PID,Dados.Prioridade);

					printf("Executando processo por 100 ut \n");
					for(i=0;i<3;i++){
						printf("Executando processo ... \n");
						sleep(2);
					}
					tempoExec = tempoExec - 100;
					emExecucao = Remove(emExecucao);

					if(tempoExec > 0){
						trataInterrupcao(1);
					}else{
						trataInterrupcao(3);
					}

					break;
			}

		}
		executando=0;
		sem_post(&semEscalonador);
	}
	sem_post(&semEscalonador);
}



