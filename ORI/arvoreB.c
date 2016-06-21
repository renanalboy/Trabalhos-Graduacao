/*
#define F 2
#include <stdio.h>
#include <stdlib.h>







typedef struct arvoreB {
   int num_chaves; //Quantidades de chaves contida no nó
   int chaves[2*F-1]; //Chaves armazenadas no nó
   struct arvoreB *filhos[2*F]; //Ponteiro para os filhos
   int n;
}arvoreB;

arvoreB* cria_No(){
       int i;
       arvoreB* x=(arvoreB*)malloc(sizeof(arvoreB));
       x->num_chaves = 1;
       x->n = 0;
       for (i=0; i<=2*F;i++)
           x->filhos[i] = NULL;
       return x;
}

void rearranja_Arvore(arvoreB* x,int i,arvoreB* y,int k){
     int j;
     arvoreB* novo = cria_No();
     novo->num_chaves = y->num_chaves;
     novo->n = F-1;

     novo->chaves[i] = k;
     //for (j=1;j<=F-1;j++){
        // novo->chaves[j] = y->chaves[j+(F-1)];

    // }


     if (y->num_chaves == 0){

         for(j=1;j<=F;j++){
             novo->filhos[j] = y->filhos[j+F];
         }

         y->n = F-1;
         for (j=x->n+1;j>=i+1;j--){
             x->filhos[j+1] = x->filhos[j];
         }

         x->filhos[i+1] = novo;
         for (j=x->n;j>=i;j--){
             x->chaves[j+1] = x->chaves[j];
         }

     }

     //x->chaves[i] = x->chaves[F];
     //x->n = x->n+1;
     x->filhos[F] = novo;
     x->num_chaves = 0;
     x->chaves[i] = y->chaves[F];



}


void insere_Simples(arvoreB* x,int k){
     int i=x->n;
     if (x->num_chaves == 1 && x->n <= F){
         while(i>=1 && k<x->chaves[i]){
             x->chaves[i+1] = x->chaves[i];
             i=i-1;
         }
         x->chaves[i+1] = k;
         x->n = x->n+1;

     }
     else{
    	 if (k > x->chaves[1]){
    		 insere_Simples(x->filhos[F],k);
    	 }
    	 else{
    		 insere_Simples(x->filhos[1],k);
    	 }
    	 /
          while(i>=1 && k<x->chaves[i]){
             i=i-1;
          }
          i=i+1;

          if (x->filhos[i]->n == 2*F - 1){
             rearranja_Arvore(x,i,x->filhos[i],k);
             if (k > x->chaves[i]){
                   i=i+1;
             }
             puts("Aqui");
             insere_Simples(x->filhos[i],k);
          }
          */
/*
     }


}

struct arvoreB* insere_Elemento(arvoreB** raizAtual,int k){
	arvoreB* b1 = cria_No();
	arvoreB* raiz = *raizAtual;
     if (raiz->n == 2*(F-1)) { //no raiz na capacidade máxima
          *raizAtual=b1;
          b1->num_chaves = 0;
          b1->n = 0;
          b1->filhos[1] = raiz;
          rearranja_Arvore(b1,1,raiz,k);
          //insere_Simples(b1,k);
          raiz = b1;

     }
     else{ //nó raiz com capacidade disponivel
          insere_Simples(raiz,k);

     }
     return raiz;
}

int main (){

	arvoreB* B = cria_No();
	B = insere_Elemento(&B, 2);
	printf("%d\n",B->chaves[1]);
	B = insere_Elemento(&B, 1);
	printf("%d\n",B->chaves[1]);
	B = insere_Elemento(&B, 4);
	printf("%d\n",B->chaves[1]);
	B = insere_Elemento(&B, 3);
	printf("%d\n",B->chaves[1]);
	B = insere_Elemento(&B, 7);
	printf("%d\n",B->chaves[1]);
	printf("%d\n",B->chaves[2]);
	B = insere_Elemento(&B, 6);
	printf("%d\n",B->chaves[1]);


	return 0;
}

*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#define ordem 2
#define maximoDeChaves ordem-1
/*#define minimoDeChaves (int)ceil(ordem/2.0)-1*/ //arredonda float para cima
#define minimoDeChaves 0

//typedef int TipoChave;

int nivelBusca=0;
char name[10];
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

//Função que efetiva a inserção da chave
void inserirChave(ArvoreB arvore, Arquivo arq, No *subArvDir){
int k;
int naoAchouPosicao;
k = arvore->numChaves;
naoAchouPosicao = k > 0;
while (naoAchouPosicao){
	if (arq.chave >= arvore->registros[k - 1].chave){
		naoAchouPosicao = 0;
		break;
	}
	arvore->registros[k] = arvore->registros[k - 1];
	arvore->filhos[k + 1] = arvore->filhos[k];
	k--;
	if (k < 1)
		naoAchouPosicao = 0;
}

arvore->registros[k] = arq;
arvore->filhos[k + 1] = subArvDir;
arvore->numChaves++;

}

//Função que analisa e define o melhor local para inserir
void verifica_Insercao(Arquivo arq, ArvoreB arvore, int *cresceu, Arquivo *regRetorno, ArvoreB *arvRetorno) {
No *temp;
int i, j;
	if (arvore == NULL) { //Inserir no nó anterior ou no inicio
		*cresceu = 1;
		*regRetorno = arq;
		*arvRetorno = NULL;
		return;
	}

// Percorre arvore para encontrar nó adequado
	for (i=1; i < arvore->numChaves && arq.chave > arvore->registros[i - 1].chave; i++);

	if (arq.chave == arvore->registros[i - 1].chave){ /*chave já pertence a árvore*/
		printf("\n Erro: Registro ja esta presente.\n");
		*cresceu = 0;
		return;
	}

	if (arq.chave < arvore->registros[i - 1].chave)
	 verifica_Insercao(arq, arvore->filhos[i - 1], cresceu, regRetorno,arvRetorno);
	else
		verifica_Insercao(arq, arvore->filhos[i], cresceu, regRetorno,arvRetorno);

	if (!*cresceu)
		return;
	if (arvore->numChaves < maximoDeChaves){ /* Nó tem espaço para inserção da nova chave*/
		inserirChave(arvore, *regRetorno, *arvRetorno);
		*cresceu = 0;
		return;
	}
	//Estouro na capacidade do nó - realizará divisão
	temp = (No *) malloc(sizeof(No));
	temp->numChaves = 0;
	temp->filhos[0] = NULL;
	if (i <= minimoDeChaves + 1){ /*novo nó ou no nó atual*/
		inserirChave(temp, arvore->registros[maximoDeChaves - 1],arvore->filhos[maximoDeChaves]);
		arvore->numChaves--;
		inserirChave(arvore, *regRetorno, *arvRetorno);
	}
	else{
		inserirChave(temp, *regRetorno, *arvRetorno);
	}

	for (j = minimoDeChaves + 2; j <= maximoDeChaves; j++)
		inserirChave(temp, arvore->registros[j - 1], arvore->filhos[j]);


	arvore->numChaves = minimoDeChaves;
	temp->filhos[0] = arvore->filhos[minimoDeChaves + 1];
	*regRetorno = arvore->registros[minimoDeChaves];
	*arvRetorno = temp;

}

void percursoInOrdem(ArvoreB arvore)
{
if (arvore != NULL){
int i;
for (i=0; i<arvore->numChaves; i++){
percursoInOrdem(arvore->filhos[i]);

printf("%d ", arvore->registros[i].chave);
}
percursoInOrdem(arvore->filhos[i]);
}
}



void inserir_Elemento(Arquivo arq, ArvoreB *arvore){
int cresceu;
Arquivo regRetorno;
No *filhoDir;
No *novaRaiz;

verifica_Insercao(arq, *arvore, &cresceu, &regRetorno, &filhoDir);

if (cresceu) { //A altura aumentará com a inserção de nova raiz
	novaRaiz = (No *) malloc(sizeof(No));
	novaRaiz->numChaves = 1;
	novaRaiz->registros[0] = regRetorno;
	novaRaiz->filhos[1] = filhoDir;
	novaRaiz->filhos[0] = *arvore;

	*arvore = novaRaiz;

}

}


ArvoreB buscaEmArvoreB (int chave, ArvoreB arvore){
puts("entrada busca");

if (arvore != NULL){
	int i;
	for (i=0; i<arvore->numChaves && arvore->registros[i].chave<chave; i++);
		if (i+1>arvore->numChaves || arvore->registros[i].chave > chave){
			nivelBusca++;
			return buscaEmArvoreB(chave,arvore->filhos[i]);

		}
		else{
			puts("Achei");
			FILE *arq;
			char info[100];
			sprintf(name, "%d", chave);
			arq = fopen(strcat(name,".txt"), "r");
			while( (fgets(info, sizeof(info), arq)!=NULL)){
						printf("%s",info);
			}
			fclose(arq);
			printf("%d",nivelBusca);
			nivelBusca=0;
			return arvore;
		}
}
else{
	puts("Achei");
	FILE *arq;
	char info[100];
	sprintf(name, "%d", chave);
	arq = fopen(strcat(name,".txt"), "r");
	while( (fgets(info, sizeof(info), arq)!=NULL)){
					printf("%s",info);
	}
	fclose(arq);
	printf("%d",nivelBusca);
	nivelBusca=0;
	//return arvore;
	return arvore;
}
}

/*

int main (){

	FILE *ind;
	ArvoreB B = NULL;
	Arquivo k;
	int vetor[500000];
	int aux [500000];
	int i=0;
	int ran;
	int tam;

	ind = fopen("indice.txt", "r");


	srand((unsigned)time(NULL));
	while(!feof(ind) ) {
	fscanf(ind,"%d",&vetor[i]) ;
	printf("%d",vetor[i]);
	aux[i] = vetor[i];
	i++;
	}
	tam = i;
	i=i-2;

	while(i >= 0){
		ran = (0 + (rand()%(tam)));
		printf("%d",ran);
		if (aux[ran] == 0){
			puts ("P");
			//break;
		}
		else{
		k.chave = aux[ran];
		aux[ran] = 0;
		inserir_Elemento(k,&B);
		i--;
		}
	}

	percursoInOrdem(B);


	return 0;
}
*/
