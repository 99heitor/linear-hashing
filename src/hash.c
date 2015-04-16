#include "hash.h"

void NewIndexFile (){

	FILE* arquivozinho;
	int buffer[6];
	char buffer2[256*4];

	arquivozinho = fopen ("sgbd", "wb"); //cria arquivo "sgbd" que será nosso arquivo de índice

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
}
