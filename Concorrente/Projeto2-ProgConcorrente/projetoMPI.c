/*
 * progconc.c
 *
 *  Created on: 27/11/2015
 *      Author: renan
 */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <mpi.h>

int rank, size, type = 99;

FILE *arq, *pre;

int Gera_randon(){

	int gerar;

	gerar = rand() % 1101;

	return gerar;

}

int PontoDeCela(int **M, int linha, int coluna, int argc, char* argv[]){

	MPI_Init(&argc,&argv);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);


	int i = 0, j = 0, k = 0, l = 0;
	int menor, maior, quantidade;
	int cont = 0;
	int colunaSup = 0, colunaInf = 0, linhaDir = 0, linhaEsq = 0;
	int n = linha, m = coluna;
	int qnt = 5;

	menor = M[i][j];
	maior = M[i][j];

	k = i; l = j;

	MPI_Bcast(&linha, 1, MPI_INT, 0, MPI_COMM_WORLD);
	MPI_Bcast(&coluna, 1, MPI_INT, 0, MPI_COMM_WORLD);
	MPI_Bcast(&qnt, 1, MPI_INT, 0, MPI_COMM_WORLD);


	for(i = 0; i < linha; i++){
		//Localiza menor elemento da linha, alterando apenas o valor da coluna da matriz
		if( i <= 6){
		   linhaEsq = 0;
		}else{
		   linhaEsq = i - 5;
		}
		if(n - i < 5){
		   linhaDir = n;
		}else{
		   linhaDir = i + 5;
		}

		MPI_Barrier(MPI_COMM_WORLD);
		for(j = linhaEsq; j < linhaDir; j++){
			if(menor > M[i][j]){
				menor = M[i][j];
				l = j;         //Armazena a posição do menor elemento da linha
			}
		}

		j=0;
		maior = M[0][l];

		MPI_Barrier(MPI_COMM_WORLD);
		//Estabelece limites para cima e para baixo da coluna
		//cujo valor foi dado como mínimo na linha
		if( l <= 6){
		   colunaInf = 0;
	    }else{
	    	colunaInf = l - 5;
		        }
		if(m - l < 5){
		    colunaSup = m;
		}else{
		    colunaSup = colunaSup + 5;
		}

		MPI_Barrier(MPI_COMM_WORLD);
		//Localiza maior elemento da coluna, alterando somente o numero da linha da matriz
		for(k = colunaInf; k < colunaSup; k++){
			if(maior < M[k][l]){
				maior = M[k][l];
			}
		}


		if(menor == maior){
			//printf("Ponto [%d][%d] é ponto de cela, com valor %d \n", i, j, menor);
			cont ++;
		}

	}

	MPI_Finalize();

	return cont;

}

void main(int argc, char* argv[]){

	printf(" \n");

	int linha = 20000, coluna = 20000;
	int i, j;
	int num, total = 0;
	int **M;
	int cont, inicio, fim;

	M = malloc (linha * sizeof (int *));
	for (i = 0; i < linha; ++i)
		M[i] = malloc (coluna * sizeof (int));

	/*printf("Numero de linhas:");
	scanf("%d", &linha);
	printf("Numero de colunas:");
	scanf("%d", &coluna);*/

	//Esses valores definem o tamanho da matriz para realizar cada teste com os tamanhos variados
	//de matriz basta alterar eles.
	linha = 500;
	coluna = 1500;

	srand(time(NULL));

	printf("\n");

	pre = fopen("pressao1.txt","w");

	for(i = 0; i < linha; i++){
		for(j = 0; j < coluna; j++){
			num = Gera_randon();
			M[i][j] = num;
			fprintf(pre, "  %d  ",num);
			//printf("%d - posicao [%d][%d]",num, i, j);
		}
		//printf("\n");
	}

	inicio = clock();

	total = PontoDeCela(M, linha, coluna, argc, argv);
	fim = clock();
	fim = fim - inicio;

	arq = fopen("4000x500mpi.txt", "a");
	fprintf(arq, "%d \n", fim);

	fclose(arq);

	printf("Foram encontrados %d pontos de cela.\n", total);
	printf("Tempo de execução: %d ms", fim);
	printf("\n \n");

	free(M);

}
