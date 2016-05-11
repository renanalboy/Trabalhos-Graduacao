OBJS=main.o funcoes.o threads.o -lpthread
all: projeto3
projeto3: $(OBJS)
	gcc $(OBJS) -o $@
main.o: main.c
	gcc -c main.c -o main.o
funcoes.o: funcoes.c
	gcc -c $< -o $@
threads.o: threads.c
	gcc -c $< -o $@