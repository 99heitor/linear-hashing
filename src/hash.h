#include <stdlib.h>
#include <stdio.h>
#include "estruturas.h"

unsigned char ratio;
unsigned int nBuckets; //nº de buckets na rodada. Dobra quando next == nBuckets (ou algo assim)
unsigned int next; //recebe (next+1)%nBuckets
unsigned int usedSlots;	//aumenta em 1 quando insere entry 
unsigned int allSlots; //aumenta em 28 quando splitar
unsigned int mod; //aplica-se a função mod mod e se o resultado for menor que next, aplicar a função mod 2*mod

unsigned int funcaoHash(unsigned int);
void insertEntry(FILE*, dataEntry); 
void removeEntry(FILE*, int key);
dataEntry searchEntry(FILE*, int key);
void splitBucket(FILE*); 