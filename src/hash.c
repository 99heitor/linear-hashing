#include "hash.h"
#include "io.h"

unsigned int funcaoHash(unsigned int key) {
	return ((key%header[5])<header[2])?(key%header[5]):(key%(header[5]*2));
}


void insertEntry(dataEntry new_entry,int troca){
	int i = 0,found = 0;
	unsigned int nbucket;
	if (!troca)
		nbucket = funcaoHash(new_entry.key);
	else
		nbucket = header[6];

	bucket* new_entry_bucket;
	new_entry_bucket = recuperarBucket(nbucket,troca);

	while ((i<28)&&(!found)) {
		if (new_entry_bucket->freeSpace[i] == 0){
			new_entry_bucket->entries[i].key = new_entry.key;
			new_entry_bucket->entries[i].rid = new_entry.rid;
			new_entry_bucket->freeSpace[i] = 1;
			escreverBucket(nbucket, new_entry_bucket,troca);
			found = 1;	
		}
		i++;
	}
}

dataEntry* searchEntry(unsigned int key,int troca){
	bucket* temp = recuperarBucket(funcaoHash(key),troca);
	for(int i=0;i<28;i++){
		if (temp->entries[i].key == key)
			return (temp->entries);
	}
	return &((dataEntry){0,0});
}

void split(){ //a treta
	if (((float)header[3]/(float)header[4])*100 > header[0]) {
		bucket *bucketSplitado = recuperarBucket(header[2],0);
		bucket *bucketBrother = malloc(sizeof(bucket));
		int terminei;
		while (!terminei) {
			for (int i=0,j=0;((i<28)&&(j<28));i++) {
				if ((bucketSplitado->entries[i].key)%((header[5])*2) != header[2])	 {
					bucketBrother->entries[j] = bucketSplitado->entries[i];
					bucketBrother->freeSpace[j] = 1;
					j++;

					bucketSplitado->entries[i].key = 0;
					bucketSplitado->entries[i].rid = 0;
					bucketSplitado->freeSpace[i] = 0;
				}
				
			}
			if ((bucketSplitado->overflow)!=0)
					bucketSplitado = recuperarBucket(bucketSplitado->overflow,1);
			else
				terminei = 1;
		}
		escreverBucket((header[1]+header[2]),bucketBrother,0);
		header[4]+=28;
		header[2] = ((header[2]+1)%header[1]);
		if (header[2] == 0){
			header[5] = header[5]*2;
			header[1] = header[1]*2;
		}
	}
}