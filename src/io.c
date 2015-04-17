#include "estruturas.h"	
#include "io.h"

unsigned int header[] = {70,4,0,0,112,4};

unsigned int entryPosition(unsigned int bucketPos, int entryPos) {
	return (HEADER_SIZE + bucketPos*(sizeof(bucket)) + entryPos*sizeof(dataEntry));
}

void NewIndexFile (){

	FILE* arquivozinho, *overflow;
	char buffer[256*header[1]];

	arquivozinho = fopen ("indice", "wb"); //cria arquivo "indice" que será nosso arquivo de índice

	fwrite(header, 4, 6, arquivozinho); //escreve irformações do header no arquivo

	for (int i=0;i<256*header[1];i++){
		buffer[i]=0;
	}

	fwrite(buffer, 1, 256*header[1], arquivozinho); //escreve conteúdo inicial dos buckets iniciais

	fclose(arquivozinho);

	overflow = fopen ("overflow", "wb");
	fwrite(&(0),4,1,overflow);
	fclose(overflow);
}


bucket* recuperarBucket(FILE* indice, unsigned int bucketNumber) {

	unsigned int byte = entryPosition(bucketNumber,0);
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
		

void escreverBucket (FILE* indice, unsigned int bucketNumber, bucket *escrito) {

	fseek(indice,entryPosition(bucketNumber,0),SEEK_SET);	
	for (int i=0;i<28;i++) {
		fwrite (&(escrito->entries[i].key),4,1,indice);
		fwrite (&(escrito->entries[i].rid),4,1,indice);
	}
	for (int i=0;i<28;i++)
		fwrite (&(escrito->freeSpace[i]),1,1,indice);
	
	fwrite(&(escrito->overflow),4,1,indice);
}