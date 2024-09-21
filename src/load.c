#include "load.h"

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

  block *blocks = (block*)malloc(sizeof(block) * nlines);

  int i = 0;
  int maxlen = 0;
  char *longest;
  ssize_t read = 0;
  while((read = getline(&line, &len , file)) != -1){
    sscanf(line, "%s %d %d %d",blocks[i].name, &blocks[i].x, &blocks[i].y, &blocks[i].z);
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
