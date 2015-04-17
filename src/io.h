#include <stdlib.h>
#include <stdio.h>

#define HEADER_SIZE 24

unsigned int header[6];
//ratio
//nBuckets: nº de buckets na rodada. Dobra quando next == nBuckets (ou algo assim)
//next: recebe (next+1)%nBuckets
//usedSlots: aumenta em 1 quando insere entry 
//allSlots: aumenta em 28 quando splitar
//mod: aplica-se a função mod mod e se o resultado for menor que next, aplicar a função mod 2*mod


bucket* recuperarBucket(FILE*, unsigned int);
void escreverBucket (FILE*, unsigned int, bucket*);
unsigned int entryPosition(unsigned int, int);

void NewIndexFile();