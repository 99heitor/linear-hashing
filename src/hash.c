#include "hash.h"
#include "io.h"

unsigned int funcaoHash(unsigned int key) {
	return ((key%header[5])<header[2])?(key%header[5]):(key%(header[5]*2));
}

void updateHeader(){

} 

void insertEntry(FILE* indice, dataEntry new_entry){
	int i = 0,found = 0;

	unsigned int nbucket = funcaoHash(new_entry.key);

	bucket* new_entry_bucket;
	new_entry_bucket = recuperarBucket(indice, nbucket);

	while ((i<28)&&(!found)) {
		if (new_entry_bucket->freeSpace[i] == 0){
			new_entry_bucket->entries[i].key = new_entry.key;
			new_entry_bucket->entries[i].rid = new_entry.rid;
			new_entry_bucket->freeSpace[i] = 1;
			escreverBucket(indice, nbucket, new_entry_bucket);
			found = 1;	
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

