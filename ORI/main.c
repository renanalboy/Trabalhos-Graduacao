#include "arvoreB.h"
#include "arvoreBinaria.h"
#include "arvoreAVL.h"

int main(){
		FILE *ind;
		ArvoreB B = NULL;
		Arquivo k;
		ArvoreBinaria b = NULL;
		ArvAVL A = NULL;
		int vetor[500000];
		int aux [500000];
		int i=0;
		int ran;
		int tam;
		int num;
		int b1;
		int cont = 0;

		ind = fopen("indice.txt", "r");


		srand((unsigned)time(NULL));
		while(!feof(ind) ) {
		fscanf(ind,"%d",&vetor[i]) ;
		printf("%d",vetor[i]);

		i++;
		}
		for(b1=0; b1 < i; b1++){
			aux[b1] = vetor[b1];
		}
		tam = i;
		i=i-2;

		//Insere nas arvores
		while(i >= 0){
			ran = (0 + (rand()%(tam)));
			printf("%d",ran);
			if (aux[ran] == 0){
				puts ("P");
				//break;
			}
			else{
			k.chave = aux[ran];
			num = aux[ran];
			aux[ran] = 0;
			inserir_Elemento(k,&B);
			b = inserir(b,num);
			A = insere_ArvAVL(&A,num);
			i--;
			}
		}
		puts("Arvore B");
		percursoInOrdem(B);

		//Realiza sequencias de busca
		srand((unsigned)time(NULL));
		while(cont < 5){
			puts("here");
			ran = (0 + (rand()%(tam-1)));
			puts ("Prob");
			printf("%d",ran);
			printf("%d",vetor[ran]);


			buscaEmArvoreB(vetor[ran],B);
			puts("REtorno");
			procurar(b, vetor[ran]);
			procurarAVL(A,vetor[ran]);
			cont++;
		}


	return 0;
}
