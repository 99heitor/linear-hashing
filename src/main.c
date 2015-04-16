#include "hash.h"
#include "io.h"

int main(){
	dataEntry testEntry;
	testEntry.key = 50;
	testEntry.rid = 123;
	//printf("O tamanho da coisa é: %zu \n",sizeof(bucket));
	NewIndexFile();

	FILE* indice = fopen ("indice", "r+b");
	

	/*for (int i=0;i<28;i++){
		printf ("%d\n",teste->entries[i].rid);
	}*/

	//printf("oi\n");

	insertEntry(&indice, testEntry);

	fclose(indice);
	return 0;
}
