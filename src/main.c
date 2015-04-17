#include "hash.h"
#include "io.h"

int main(){

	//dataEntry* testEntry;

	
	NewIndexFile();


	FILE* indice = fopen ("indice", "r+b");
	
	for (int i=0;i<1;i++){
		insertEntry((dataEntry){12,141},0);
	}

	/*for (int i=0;i<28;i++){
		printf ("%d\n",teste->entries[i].rid);
	}*/

	//printf("oi\n");


	//insertEntry(indice, &((dataEntry){31,1000}));
	//testEntry = searchEntry(indice,50);
	//printf("%u %u\n",testEntry->key,testEntry->rid);

	fclose(indice);

	return 0;
}
