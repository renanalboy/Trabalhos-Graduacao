%{
	#include "cabecalho.h"
	#include <stdio.h>
	#include <stdlib.h>

	int yywrap();
	extern int linhas;
	extern int erros;
	
%}

%token ABRE_PARENTESES FECHA_PARENTESES
%token ABRE_CHAVE FECHA_CHAVE SEPARADOR SIMBOLO
%token MAIN IF ELSE WHILE FOR RETURN DO INT FLOAT DOUBLE LONGINT
%token COMENTARIO BIBLIOTECA ID STRING DECLARACAO 
%token LOGICO OPERADOR COMPARACAO NUMERO PRINT
%start Programa_principal

%%

//programa principal
Programa_principal: MAIN ABRE_PARENTESES FECHA_PARENTESES ABRE_CHAVE  Comandos FECHA_CHAVE 
| error {yyerror("", linhas); }
;

Comandos: Comando Comandos 
| Comando 
;

Comando: Declaracao 
| Atribuicao 
| Print 
| For
| While 
| If 
| DoWhile
| Comentario
| Operacao
| error {yyerror("",linhas); }
;

Comentario: COMENTARIO;

Operacao: ID COMPARACAO ID OPERADOR NUMERO SEPARADOR;

OperacaoFor: ID COMPARACAO ID OPERADOR NUMERO

Print: PRINT ABRE_PARENTESES STRING FECHA_PARENTESES SEPARADOR;

Tipo: INT 
| FLOAT 
| DOUBLE 
| LONGINT
;

For: FOR ABRE_PARENTESES ID COMPARACAO NUMERO SEPARADOR ID COMPARACAO NUMERO SEPARADOR OperacaoFor FECHA_PARENTESES ABRE_CHAVE Comandos FECHA_CHAVE 
;

While: WHILE ABRE_PARENTESES ID COMPARACAO NUMERO FECHA_PARENTESES ABRE_CHAVE Comandos FECHA_CHAVE 
;

If: IF ABRE_PARENTESES ID COMPARACAO NUMERO FECHA_PARENTESES ABRE_CHAVE Comandos FECHA_CHAVE 
;

DoWhile: DO ABRE_CHAVE Comandos FECHA_CHAVE WHILE ABRE_PARENTESES ID COMPARACAO NUMERO FECHA_PARENTESES SEPARADOR
;

Declaracao: Tipo ID SEPARADOR;

Atribuicao: ID COMPARACAO NUMERO SEPARADOR 
;

%%

FILE *yyin;	
	int yyerror(char *str, int num_linha) {
	if(strcmp(str,"syntax error")==0){
		erros++;
		printf("Erro sintático\n");//Exibe mensagem de erro
	}
	else
	{
		printf("O erro aparece próximo à linha %d\n",
		num_linha);//Exibe a linha do erro
	}
	return erros;
}

main (int argc, char **argv )
{
	++argv, --argc; //desconsidera o nome do programa
	if ( argc > 0 )
		yyin = fopen( argv[0], "r" );
	else
	{
		puts("Falha ao abrir arquivo, nome incorreto ou não especificado. Digite o comando novamente.");
		 //exibe
		//mensagem de texto se o arquivo não for especificado ou for
		//especificado com o nome errado
		exit(0);
	}
	do {
	yyparse();
	} while (!feof(yyin));//enquanto não chegar ao fim do arquivofaz as análises
		if(erros==0)//Se não houver erros, imprime mensagem defim de análise com sucesso
		puts("Análise concluída com sucesso");
}

	
