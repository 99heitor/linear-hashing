#include <stdlib.h>
#include <stdio.h>

typedef struct _dataEntry {
	unsigned int rid;
	unsigned int key;
} dataEntry;

typedef struct _bucket {	
	dataEntry entries[28];
	char freeSpace[28];
	unsigned int overflow;
} bucket;


//Ceci n'est pas une struct
typedef struct _header {
	char ratio;
	
	unsigned int nBuckets; //nº de buckets na rodada. Dobra quando next == nBuckets (ou algo assim)
	unsigned int next; //recebe (next+1)%nBuckets
	unsigned int usedSlots;	//aumenta em 1 quando insere entry 
	unsigned int allSlots; //aumenta em 28 quando splitar
	unsigned int mod; //aplica-se a função mod mod e se o resultado for menor que next, aplicar a função mod 2*mod
}header;

