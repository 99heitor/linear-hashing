#include "estruturas.h"	
#include "io.h"

unsigned int header[] = {50,4,0,0,112,4,0};


void updateHeader(FILE* indice) {
	rewind(indice);
	fwrite(header, 4, 7, indice); //escreve irformações do header no arquivo
}


unsigned int entryPosition(unsigned int bucketPos, int entryPos, int troca) {	
	if (!troca)
		return (HEADER_SIZE + bucketPos*(sizeof(bucket)) + entryPos*sizeof(dataEntry));
	else
		return ((bucketPos-1)*(sizeof(bucket)) + entryPos*sizeof(dataEntry));
}

void NewIndexFile (){

	FILE* arquivozinho, *overflow;
	//char buffer[256*header[1]];
	char zero = 0;

	arquivozinho = fopen ("indice", "wb"); //cria arquivo "indice" que será nosso arquivo de índice

	fwrite(header, 4, 7, arquivozinho); //escreve irformações do header no arquivo
	
	for (int i=0;i<(256*header[1] + 100);i++){
		fwrite(&zero, 1, 1, arquivozinho);	
	}

	fclose(arquivozinho);

	overflow = fopen ("overflow", "wb");
	fclose(overflow);
}


bucket* recuperarBucket(FILE* indice,unsigned int bucketNumber,int troca) {
	//extern FILE* indice;

	unsigned int byte = entryPosition(bucketNumber,0,troca);
	fseek(indice,byte,SEEK_SET);	
	bucket* recuperado;
	recuperado = malloc(sizeof(bucket));

	for (int i=0;i<28;i++) {
		fread (&(recuperado->entries[i].key),4,1,indice);
		fread (&(recuperado->entries[i].rid),4,1,indice);
	}
	for (int i=0;i<28;i++)
		fread (&(recuperado->freeSpace[i]),1,1,indice);

	fread(&(recuperado->overflow),4,1,indice);

	return recuperado;
}
		
void escreverBucket (FILE* indice, unsigned int bucketNumber, bucket* escrito,int troca) {
	fseek(indice,entryPosition(bucketNumber,0,troca),SEEK_SET);	
	for (int i=0;i<28;i++) {
		fwrite (&(escrito->entries[i].key),4,1,indice);
		fwrite (&(escrito->entries[i].rid),4,1,indice);
	}
	for (int i=0;i<28;i++)
		fwrite (&(escrito->freeSpace[i]),1,1,indice);

	fwrite(&(escrito->overflow),4,1,indice);
}
