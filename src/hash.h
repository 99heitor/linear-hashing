#include <stdlib.h>
#include <stdio.h>

void insert(*FILE, dataEntry); 
void remove(*FILE, int key);
dataEntry search(*FILE, int key);
void split(*FILE); 