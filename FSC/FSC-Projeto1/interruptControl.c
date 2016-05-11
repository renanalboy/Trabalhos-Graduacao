
#include "Biblioteca.h"

void interruptControl(){
	int num;


	srand( (unsigned) time(NULL) );
	num = (rand()%20);

	printf("Gerando número randomico ... \n");
	printf("Gerado o número : %d \n", num);
}
