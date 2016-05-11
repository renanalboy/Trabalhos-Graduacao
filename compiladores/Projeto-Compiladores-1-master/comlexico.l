%{
	#include <stdio.h>	
	int linhas=1; 
	int erros=0;
%}

ID		[a-zA-Z0-9_]
DIGITO		[0-9]
ESPACO		[\ \t\n]
LETRA		[a-zA-Z]
OPERADOR	[-|+|*|/]
LOGICO		[|| | &&]
COMPARA		[ > | >= | < | <= | == | !=]
SIMBOLO		[ ( | ) | { | } | , | ; | _ ]
ASPAS		["]
RESERVADO	[if | else | while | for | return | do | int | float]


%%
\n {linhas++;}

{ESPACO} { }

"//"({LETRA}*|{ESPACO}*|{DIGITO}*)* {
	printf("Comentario:%s\n",yytext);
}

"#"{LETRA}*{ESPACO}*"<"{LETRA}*".h"">" {
	printf("Biblioteca:%s\n",yytext);
}

({LETRA}+{ID}*) {
	printf(" Identificador:%s\n", yytext);
}

{ASPAS}({LETRA}*|{ESPACO}*|{DIGITO}*)*{ASPAS} {
	printf("String:%s\n",yytext);
}

({DIGITO}{DIGITO}*)* {
	printf("Digito inteiro:%s\n",yytext);
}

({DIGITO}+.{DIGITO}+)* {
	printf("Digito real:%s\n",yytext);
}

{LOGICO} {
	printf(" Simbolo logico:%s\n",yytext);
}


{OPERADOR} {
	printf("Simbolo de operador:%s\n",yytext);
}


{COMPARA}* {
	printf("Simbolo de comparacao:%s\n",yytext);
}

{SIMBOLO} {
	printf("Simbolo de separacao:%s\n",yytext);
}

{RESERVADO} {
	printf("Simbolo reservado:%s\n",yytext);
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

%%

int yywrap();
int main(int argc, char **argv){
	
	yylex();
	printf("Fim da analise lexica \n");
	if (erros > 0){
	printf("Numero de erros encontrados:%d\n",erros);
	}
	else {
	printf("Sem erros léxicos \n");	
	}
}

int yywrap(){
	return 1;
}


