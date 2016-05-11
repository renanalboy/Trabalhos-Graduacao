OBJS=main.o nucleo.o lista.o -lpthread
all: projeto2
projeto2: $(OBJS)
	gcc $(OBJS) -o $@
main.o: main.c
	gcc -c main.c -o main.o
nucleo.o: nucleo.c
	gcc -c $< -o $@
lista.o: lista.c
	gcc -c $< -o $@
	