#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct block_{
  int x, y, z;
  char name[20];
}block;

block* loadBlocks(char* filename, int* amount);
