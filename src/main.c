#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "raylib.h"
#include <emscripten/emscripten.h>

#define EXTERN

typedef struct block_{
  int x, y, z;
  char name[20];
}block;

block* blocks = NULL;
block* bp = NULL;
int amount = 0;

EXTERN EMSCRIPTEN_KEEPALIVE void initBlocks(int amnt);
EXTERN EMSCRIPTEN_KEEPALIVE int addBlock(char* definition);

const int screenWidth = 800;
const int screenHeight = 450;

void UpdateDrawFrame(void);     // Update and Draw one frame

int main(){
  InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");
  emscripten_set_main_loop(UpdateDrawFrame, 0, 1);
  CloseWindow();

  return 0;
}

void UpdateDrawFrame(void){
  static int counter = 0;
  if(blocks == NULL){
    printf("%d: Blocks array is null.\n", counter++);
    return;
  }

  printf("amount: %d\n", amount);
  for(int i = 0; i < amount; i++){
	  printf("%d, %s\n", i, blocks[i].name);
  }

  return;
}
EXTERN EMSCRIPTEN_KEEPALIVE void initBlocks(int amnt){
  block *b = (block*)malloc(sizeof(block) * amnt);
  printf("init blocks run, allocated %d blocks\n", amnt);
  blocks = b;
  bp = blocks;
  amount = amnt;
}

EXTERN EMSCRIPTEN_KEEPALIVE int addBlock(char* definition){
	if(blocks == NULL){
		printf("error adding block, blocks array is null\n");
		return 2;
	}
	if(bp <= blocks + amount){
	    sscanf(definition, "%s %d %d %d",bp->name, &bp->x, &bp->y, &bp->z);
	    bp++;
	    printf("added block successfully\n");
	    return 0;
	} else {
		printf("block will not fit in array\n");
		return 1;
	}
	return 3;
}

