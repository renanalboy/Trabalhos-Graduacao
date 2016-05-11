%{
	#include <math.h>
	#include <stdio.h>
	#include "analisador.h"	
	
	int linhas=1; 
	int erros=0;
	int yywrap();
%}

ID		[a-zA-Z0-9_]
DIGITO		[0-9]
ESPACO		[\ \t\n]
LETRA		[a-zA-Z]
OPERADOR	[- | + | * | /]
LOGICO		[|| | &&]
COMPARA		[ > | >= | < | <= | == | != | =]
ABRE_PARENTESES	[(]
FECHA_PARENTESES [)]
ABRE_CHAVE	[{]
FECHA_CHAVE	[}]
SEPARADOR	[;]
SIMBOLO		[, | _]
ASPAS		["]
IGUAL		[=]
MAIN		[main]
IF		[if]
ELSE		[else]
WHILE		[while]
FOR		[for]
PRINT 		[printf]
RETURN		[return]
DO		[do]
INT		[int]
FLOAT		[float]
DOUBLE		[double]
LONG INT	[long int]

%%
\n {linhas++;}

{ESPACO} { }

"(" {
	return(ABRE_PARENTESES);
}

")" {
	return(FECHA_PARENTESES);
}

"{" {
	return(ABRE_CHAVE);
}

"}" {
	return(FECHA_CHAVE);
}

";" {
	return(SEPARADOR);
}

"," {
	return(SIMBOLO);
}

"_" {
	return(SIMBOLO);
}

"main" {
	return(MAIN);
}

"if" {
	return(IF);
}

"else" {
	return(ELSE);
}

"while" {
	return(WHILE);
}

"for" {
	return(FOR);
}

"printf" {
	return(PRINT);
}

"return" {
	return(RETURN);
}

"do" {
	return(DO);
}


"int" {
	return(INT);
}

"float" {
	return(FLOAT);
}

"double" {
	return(DOUBLE);
}

"long int" {
	return(LONGINT);
}

"//"({LETRA}*|{ESPACO}*|{DIGITO}*)* {
	return(COMENTARIO);
}

"#"{LETRA}*{ESPACO}*"<"{LETRA}*".h"">" {
	return(BIBLIOTECA);
}

({LETRA}+{ID}*) {
	return(ID);
}

{ASPAS}({LETRA}*|{ESPACO}*|{DIGITO}*)*{ASPAS} {
	return(STRING);
}

({DIGITO}{DIGITO}*)* {
	return(NUMERO);
}

({DIGITO}+.{DIGITO}+)* {
	return(NUMERO);
}

{LOGICO} {
	return(LOGICO);
}

{OPERADOR} {
	return(OPERADOR);
}


{COMPARA}* {
	return(COMPARACAO);
}

{DIGITO}+({LETRA}+{ID}*) {
	printf("Erro, nao reconhecido:%s,%d\n",yytext,linhas);
	erros++;	
}
[.|,]*{DIGITO}* {
	printf("Erro, nao reconhecido:%s,%d\n",yytext,linhas);
	erros++;	
}

. {
	printf("Erro, nao reconhecido:%s,%d\n",yytext,linhas);
	erros++;	
}


