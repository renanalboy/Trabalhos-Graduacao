
#include "Biblioteca.h"

void leituraArquivo(){
    FILE *arquivo;
    char linha[50], arqLido[20];
    char *linhaGuardada;
    int i;

    printf("Insira o nome do arquivo que deve ser lido:\n");
    scanf("%s", arqLido);

	printf("\n\n");

    arquivo = fopen(arqLido, "rt");

    if(arquivo == NULL){
        printf("Arquivo não encontrado.\n");
    }else{
        i = 1;

        while(!feof (arquivo)){
            linhaGuardada = fgets(linha, 50, arquivo);
            if(linhaGuardada){
                printf("Executando comando: %s \n", linha);
            }
        }
	printf("FIM!!");
    fclose(arquivo);
    }
}
