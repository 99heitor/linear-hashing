#include "hash.h"
#include "io.h"

int main(){

	NewIndexFile();


	FILE* indice = fopen ("indice", "r+b");
	FILE* overflow = fopen ("overflow", "r+b");
	
	//Escrever aqui os casos teste.

	fclose(overflow);
	fclose(indice);

	return 0;

}
