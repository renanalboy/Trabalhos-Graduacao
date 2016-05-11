#!/bin/bash

#Script para geração de analisador sintático
echo "Iniciando o BISON"
bison -d comp.y
echo "Renomeando arquivos"
mv comp.tab.h analisador.h
mv comp.tab.c comp.y.c
echo "Iniciando FLEX"
flex comp.l
echo "Renomeando arquivos"
mv lex.yy.c comp.flex.c
echo "Compilando arquivos"
gcc -c comp.flex.c -o comp.flex.o
gcc -c comp.y.c -o comp.y.o
gcc -o comp comp.flex.o comp.y.o -lfl -lm
echo "Para executar o compilador digite: ./comp compiladores.txt ou ./comp compiladores2.txt"
