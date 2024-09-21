#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "raylib.h"
#include "load.h"

int main(){
  int amount;
  block* blocks = loadBlocks("blocks.txt", &amount);
  if(blocks == NULL){
    printf("Blocks array is null, exiting.\n");
    return 1;
  }
  printf("%s\n", blocks[0].name);

  return 0;
}
