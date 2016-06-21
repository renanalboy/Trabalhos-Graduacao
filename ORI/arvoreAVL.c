

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct NO{
	int info;
	int altura;
	struct NO *esq;
	struct NO *dir;
};

typedef struct NO* ArvAVL;

int nivelBuscaAVL=0;

int altura_NO(struct NO* no){
	if(no == NULL) return -1;
	else
		return no->altura;
}

int fatorBalanceamento_NO(struct NO* no){
	return labs(altura_NO(no->esq) - altura_NO(no->dir));
}

int maior(int x, int y){
	if(x > y)
		return x;
	else
		return y;
}

void rotacaoLL(ArvAVL *raiz){
	struct NO *no;
	no = (*raiz)->esq;
	(*raiz)->esq = no->dir;
	no->dir = (*raiz);
	(*raiz)->altura = maior(altura_NO((*raiz)->esq), altura_NO((*raiz)->dir)) + 1;
	no->altura = maior(altura_NO(no->esq),(*raiz)->altura) +1;

	*raiz = no;
}

void rotacaoRR(ArvAVL *raiz){
	struct NO *no;
	no = (*raiz)->dir;
	(*raiz)->dir = no->esq;
	no->esq = (*raiz);
	(*raiz)->altura = maior(altura_NO((*raiz)->esq), altura_NO((*raiz)->dir)) +1;
	no->altura = maior(altura_NO(no->dir), (*raiz)->altura) +1;

	(*raiz) = no;
}

void rotacaoRL(ArvAVL *raiz){
	rotacaoRR(&(*raiz)->esq);
	rotacaoLL(raiz);
}

void rotacaoLR(ArvAVL *raiz){
	rotacaoLL(&(*raiz)->dir);
	rotacaoRR(raiz);
}

ArvAVL insere_ArvAVL(ArvAVL *raiz, int valor){

	if(*raiz == NULL){
		struct NO *raiz;
		raiz = (struct NO*)malloc(sizeof(struct NO));

		raiz->info = valor;
		raiz->altura = 0;
		raiz->esq = NULL;
		raiz->dir = NULL;

		return raiz;
	}

	struct NO *atual = *raiz;
	if(valor < atual->info){
		atual->esq = insere_ArvAVL(&atual->esq,valor);
		if(fatorBalanceamento_NO(atual) >= 2){
			if(valor < (*raiz)->esq->info){
				rotacaoLL(raiz);
			}else{
				rotacaoLR(raiz);
			}
		}
	}
	else{
		if(valor  > atual->info){
			atual->dir = insere_ArvAVL(&atual->dir,valor);
			if(fatorBalanceamento_NO(atual) >=2){
				if((*raiz)->dir->info < valor){
					rotacaoRR(raiz);
				}
				else{
					rotacaoRL(raiz);
				}
			}
		}
	}

	atual->altura = maior(altura_NO(atual->esq), altura_NO(atual->dir) + 1);

	return *raiz;
}

ArvAVL procurarAVL (ArvAVL raiz, int info){
	puts("Entrada AVL");
	if (!raiz){
		puts("Entrada AVL");
		FILE *arq;
		char infotexto[100];
		char name[10];
		sprintf(name, "%d", info);
		arq = fopen(strcat(name,".txt"), "r");
		while( (fgets(infotexto, sizeof(infotexto), arq)!=NULL)){
			printf("%s",infotexto);
		}
		fclose(arq);
		printf("%d",nivelBuscaAVL);
		nivelBuscaAVL=0;
		return NULL;
	}

	if (info > raiz->info){
		puts("Primeira entrada");
		nivelBuscaAVL++;
		return procurarAVL(raiz->dir, info);
	}
	else{
		nivelBuscaAVL++;
		return procurarAVL (raiz->esq, info);
	}



	return NULL;
}

/*
main(){
	ArvAVL* raiz;

	int acao, num, x;
	char continua, s, n;

	while(continua == s){

		puts("Escolha a acao:");
		puts("1 - Inserir na arvore");
		puts("2 - realizar busca");
		puts("3 - sair");
		scanf("%d", &acao);

		switch(acao){
			case 1: puts("Valor a ser inserido:");
					scanf("%d", &num);
					x = insere_ArvAVL(raiz, num);
					if(x == 1){
						puts("Inserção realizada com sucesso");
					}
					break;

			case 2:

			case 3: continua = n;
					break;
		}

	}

}
*/
