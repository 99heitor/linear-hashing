#include "hash.h"
#include "io.h"

int main(){
	//printf("O tamanho da coisa é: %zu \n",sizeof(bucket));
	NewIndexFile();

	FILE* indice = fopen ("indice", "rb");
	bucket* teste;



	teste = recuperarBucket(indice,0);


	for (int i=0;i<28;i++){
		printf ("%d\n",teste->entries[i].rid);
	}

	//printf("oi\n");



	return 0;
}
