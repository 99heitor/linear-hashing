#include <stdlib.h>
#include <stdio.h>

#define HEADER_SIZE 24


bucket* recuperarBucket(FILE*, unsigned int);
unsigned int entryPosition(unsigned int, int);

void NewIndexFile();