#include <stdlib.h>
#include <stdio.h>

#define HEADER_SIZE 28

FILE *indice,*overflow;

unsigned int header[7];
//ratio
//nBuckets: nº de buckets na rodada. Dobra quando next == nBuckets (ou algo assim)
//next: recebe (next+1)%nBuckets
//usedSlots: aumenta em 1 quando insere entry 
//allSlots: aumenta em 28 quando splitar
//mod: aplica-se a função mod mod e se o resultado for menor que next, aplicar a função mod 2*mod
//firstFree: primeiro overflow livre no arquivo "overflow"

bucket* recuperarBucket(unsigned int,int);
void escreverBucket (unsigned int, bucket*,int);
unsigned int entryPosition(unsigned int, int, int);
void updateHeader();
void NewIndexFile();