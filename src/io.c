#include "estruturas.h"	
#include "io.h"

unsigned int entryPosition(unsigned int bucketPos, int entryPos) {
	return (HEADER_SIZE + bucketPos*(sizeof(bucket)) + entryPos*sizeof(dataEntry));
}

void NewIndexFile (){

	FILE *arquivozinho, *overflow;
	int buffer[6];
	char buffer2[256*4];
	unsigned int v[] = {0};

	arquivozinho = fopen ("indice", "wb"); //cria arquivo "sgbd" que será nosso arquivo de índice

	buffer[0] = 70; //ratio
	buffer[1] = 4;	//nBuckets
	buffer[2] = 0;	//next
	buffer[3] = 0;	//usedSlots
	buffer[4] = 28*buffer[1];	//allSlots
	buffer[5] = 4;	//mod
	fwrite(buffer, 4, 6, arquivozinho); //escreve irformações do header no arquivo
	
	for (int i=0;i<256*buffer[1];i++){
		buffer2[i]=0;
	}
	fwrite(buffer2, 1, 256*buffer[1], arquivozinho); //escreve conteúdo inicial dos buckets iniciais

	fclose(arquivozinho);

	overflow = fopen ("overflow", "wb");
	fwrite(v,4,1,overflow);
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