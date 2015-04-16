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

dataEntry searchEntry(FILE* indice, unsigned int key){
	return (dataEntry){1,1};
}