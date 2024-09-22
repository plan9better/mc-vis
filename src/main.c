#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h> 
#include "raylib.h"
#include <emscripten/emscripten.h>

typedef struct block_{
  int x, y, z;
  char name[20];
}block;

block* blocks = NULL;
block* bp = NULL;
int amount = 0;

void initBlocks(int amnt);
int addBlock(char* definition);

const int screenWidth = 800;
const int screenHeight = 450;

void UpdateDrawFrame(void);     // Update and Draw one frame

int main(){
  InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");
  emscripten_set_main_loop(UpdateDrawFrame, 0, 1);
  CloseWindow();

  return 0;
}
void initBlocks(int amnt){
  block *b = (block*)malloc(sizeof(block) * amnt);
  blocks = b;
  bp = blocks;
}

int addBlock(char* definition){
	if(blocks == NULL){
		return 2;
	}
	if(bp < blocks + amount){
	    sscanf(definition, "%s %d %d %d",bp->name, &bp->x, &bp->y, &bp->z);
	    bp++;
	    return 0;
	} else {
		return 1;
	}
}
block* loadBlocks(char* filename, int *amount){
  printf("Loading files\n");
  FILE *file = fopen(filename, "r");
  if(!file){
    printf("Failed to open file\n");
    return NULL;
  }

  // count lines (blocks)
  char *line = NULL;
  size_t len = 0;
  int nlines = 0;
  while(getline(&line, &len, file) != -1){
    nlines++;
  }

  // go back to start of file
  fseek(file, 0, SEEK_SET);


  int i = 0;
  int maxlen = 0;
  char *longest;
  ssize_t read = 0;
  while((read = getline(&line, &len , file)) != -1){
    if(strlen(blocks[i].name) > maxlen){
      printf("New longest %s\n", blocks[0].name);
      longest = blocks[i].name;
      maxlen = strlen(blocks[i].name);
    }
    i++;
  }
  printf("Loaded blocks\nLongest block name(%d): %s\n", maxlen, longest);
  *amount = nlines;
  printf("%d\n", nlines);
  return blocks;
}
void UpdateDrawFrame(void){
  static int counter = 0;
  if(blocks == NULL){
    printf("%d: Blocks array is null.\n", counter++);
  } else {
	  for(int i = 0; i < amount; i++){
		  printf("%d, %s\n", i, blocks[0].name);
	  }
  }

  return;
}
