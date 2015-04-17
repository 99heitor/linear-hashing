#include "hash.h"
#include "io.h"

int main(){

	//dataEntry* testEntry;

	
	NewIndexFile();


	FILE* indice = fopen ("indice", "r+b");
	FILE* overflow = fopen ("overflow", "r+b");
	
	for (int i=0;i<260;i++){
		insertEntry(indice,overflow,&((dataEntry){10,141}));
	}

	/*for (int i=0;i<28;i++){
		printf ("%d\n",teste->entries[i].rid);
	}*/

	//printf("oi\n");

/*
	insertEntry(indice,overflow,&((dataEntry){31,1000}));
	//testEntry = searchEntry(indice,50);
	//printf("%u %u\n",testEntry->key,testEntry->rid);
}
	fclose(overflow);
	fclose(indice);

	return 0;
*/
}
