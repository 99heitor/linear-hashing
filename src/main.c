#include "hash.h"
#include "io.h"

int main(){
	dataEntry testEntry;
	testEntry.key = 50;
	testEntry.rid = 12331;
	
	//printf("O tamanho da coisa é: %zu \n",sizeof(bucket));
	NewIndexFile();

	FILE* indice = fopen ("indice", "r+b");
	

	/*for (int i=0;i<28;i++){
		printf ("%d\n",teste->entries[i].rid);
	}*/

	//printf("oi\n");

	insertEntry(indice, testEntry);
	testEntry = searchEntry(indice,50);
	//printf("%u %u\n",testEntry.key,testEntry.rid);
	fclose(indice);
	return 0;
}
