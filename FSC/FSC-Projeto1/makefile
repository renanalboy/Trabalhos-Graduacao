OBJS=main.o interruptControl.o leituraArquivo.o
all: projeto
projeto: $(OBJS)
	gcc $(OBJS) -o $@
main.o: main.c
	gcc -c main.c -o main.o
leituraArquivo.o: leituraArquivo.c
	gcc -c $< -o $@
interruptControl.o: interruptControl.c
	gcc -c $< -o $@
	