#include "hash.h"
#include "io.h"

unsigned char ratio = 70;
unsigned int nBuckets = 4; //nº de buckets na rodada. Dobra quando next == nBuckets (ou algo assim)
unsigned int next = 0; //recebe (next+1)%nBuckets
unsigned int usedSlots = 0;	//aumenta em 1 quando insere entry 
unsigned int allSlots = 28*4; //aumenta em 28 quando splitar
unsigned int mod = 4; //aplica-se a função mod mod e se o resultado for menor que next, aplicar a função mod 2*mod


unsigned int funcaoHash(unsigned int key) {
	return ((key%mod)<next)?(key%mod):(key%(mod*2));
}

void insertEntry(FILE* indice, dataEntry new_entry){
	int i = 0,found = 0;

	unsigned int nbucket = funcaoHash(new_entry.key);
	unsigned int buffer[2];

	bucket* new_entry_bucket;
	new_entry_bucket = recuperarBucket(indice, nbucket);

	while ((i<28)&&(!found)) {
		if (new_entry_bucket->freeSpace[i] == 0){
			fseek(indice,entryPosition(nbucket,i),SEEK_SET);
			buffer[0] = new_entry.key;
			buffer[1] = new_entry.rid;
			fwrite(buffer,4,2,indice);
			found=1;
		}
		i++;
	}
}

dataEntry* searchEntry(FILE* indice, unsigned int key){
	bucket* temp = recuperarBucket(indice,funcaoHash(key));
	for(int i=0;i<28;i++){
		if (temp->entries[i].key == key)
			return (temp->entries);
	}
	return &((dataEntry){0,0});
}