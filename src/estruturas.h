
#include <stdlib.h>
#include <stdio.h>

typedef struct _dataEntry {
	unsigned int key;
	unsigned int rid;
} dataEntry;

typedef struct _bucket {	
	dataEntry entries[28];
	char freeSpace[28];
	unsigned int overflow;
} bucket;	

/*
//Ceci n'est pas une struct
typedef struct _header {

}header;
*/
