#include "hash.h"
#include "io.h"

unsigned int funcaoHash(unsigned int key) {
	return ((key%header[5])>header[2])?(key%header[5]):(key%(header[5]*2));
}
/*

void insertEntry(FILE* indice, FILE* overflow, dataEntry* new_entry){

	int found = 0,i,consegui;
	unsigned int nbucket = funcaoHash(new_entry->key);
	bucket *new_entry_bucket = recuperarBucket(indice,nbucket,0);

	bucket* new_overflow;

	while ((i<28)&&(!found)) {
		if (!(new_entry_bucket->freeSpace[i])){ //se o espaço "está" vazio
			new_entry_bucket->entries[i].key = new_entry->key;
			new_entry_bucket->entries[i].rid = new_entry->rid;
			new_entry_bucket->freeSpace[i] = 1;
			escreverBucket(indice,nbucket,new_entry_bucket,0);
		}
		i++;
	}
	if (!found){
		while(!consegui){
			if (new_entry_bucket->overflow == 0){
				new_overflow = malloc(sizeof(bucket));
				new_overflow->entries[0].key = new_entry->key;
				new_overflow->entries[0].rid = new_entry->rid;
				new_overflow->freeSpace[0] = 1;
				for (int j=1;j<28;j++){
					new_overflow->entries[j].key = 0;
					new_overflow->entries[j].rid = 0;
					new_overflow->freeSpace[j] = 0;
				}
				new_overflow->overflow = 0;
				new_entry_bucket->overflow = header[6];
				escreverBucket(indice,nbucket,new_entry_bucket,0);
				escreverBucket(overflow, header[6],new_overflow,1);
				header[6]++;
				updateHeader(indice);
				consegui = 1;
			}
		}
	}
	header[3]++;
	updateHeader(indice);
	split(indice);
}
*/
void insertEntry(FILE* indice, FILE* overflow, dataEntry* new_entry) {
	int i = 0,found = 0, consegui = 0;
	unsigned int nbucket, nOverflow;
	nbucket = funcaoHash(new_entry->key);

	bucket* new_entry_bucket, *new_overflow;
	new_entry_bucket = recuperarBucket(indice,nbucket,0);
	while ((i<28)&&(!found)) {
		if (new_entry_bucket->freeSpace[i] == 0){
			new_entry_bucket->entries[i].key = new_entry->key;
			new_entry_bucket->entries[i].rid = new_entry->rid;
			new_entry_bucket->freeSpace[i] = 1;
			escreverBucket(indice, nbucket, new_entry_bucket,0);
			found = 1;	
		}
		i++;
	}
	if (!found){
		while(!consegui) {
			//printf("oi\n");
			if(new_entry_bucket->overflow == 0){	//se não existir bucket overflow
				//printf("oi2\n");
				new_overflow = malloc(sizeof(bucket));
				new_overflow->entries[0].key = new_entry->key;
				new_overflow->entries[0].rid = new_entry->rid;
				new_overflow->freeSpace[0] = 1;
				for (int j=1;j<28;j++){
					new_overflow->entries[j].key = 0;
					new_overflow->entries[j].rid = 0;
					new_overflow->freeSpace[j] = 0;
				}
				new_overflow->overflow = 0;
				new_entry_bucket->overflow = header[6];
				escreverBucket(indice,nbucket,new_entry_bucket,0);
				escreverBucket(overflow, header[6],new_overflow,1);
				header[6]++;
				printf("Headerfree %d\n",header[6]);
				updateHeader(indice);
				consegui = 1;
			}
			else{		//se existir bucket overflow
				//printf("oi3\n");
				nOverflow = new_entry_bucket->overflow;
				new_entry_bucket = recuperarBucket(overflow, new_entry_bucket->overflow,1);
				i=0;
				while ((i<28)&&(!found)) {
					if (new_entry_bucket->freeSpace[i] == 0){
						new_entry_bucket->entries[i].key = new_entry->key;
						new_entry_bucket->entries[i].rid = new_entry->rid;
						new_entry_bucket->freeSpace[i] = 1;
						escreverBucket(overflow, nOverflow, new_entry_bucket,1);
						found = 1;	
						consegui = 1;
						printf("oi\n");
					}
					i++;
				}
			}
		}
	}

	header[3]++;
	updateHeader(indice);
}

dataEntry* searchEntry(FILE* indice,unsigned int key,int troca){
	bucket* temp = recuperarBucket(indice, funcaoHash(key),troca);
	for(int i=0;i<28;i++){
		if (temp->entries[i].key == key)
			return (temp->entries);
	}
	return &((dataEntry){0,0});
}

void removeEntry(FILE* indice, unsigned int key, int troca) {
	bucket* temp = recuperarBucket(indice, funcaoHash(key),troca);
	for(int i=0;i<28;i++){
		if (temp->entries[i].key == key){
			temp->entries[i].key = 0;
			temp->entries[i].rid = 0;
			break;
		}
		escreverBucket(indice, funcaoHash(key), temp, 0);
	}
	header[3]--;
	updateHeader(indice);
	//return &((dataEntry){0,0});
}


