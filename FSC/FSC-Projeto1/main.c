
#include "Biblioteca.h"

int main(){
    int opcao;

    printf("\n\n");

    printf("Bem vindo! Selecione a opção que deseja executar:\n\n");
    printf("[1] - Leitura de arquivo\n");
    printf("[2] - Gerar um número randomico\n\n");
    scanf("%d", &opcao);

	printf("\n\n");

    if(opcao == 1){
            leituraArquivo();
    }else{
        if(opcao == 2){
            interruptControl();
        }else{
            printf("Valor inválido.\n\n");
            return 0;
        }
    }

	return 1;

	system("pause");
}
