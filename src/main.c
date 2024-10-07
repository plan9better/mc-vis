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
static Camera3D camera = { 0 };

int main(){
  InitWindow(screenWidth, screenHeight, "mc-vis");
camera.position = (Vector3){ 30.0f, 20.0f, 30.0f }; // Camera position
camera.target = (Vector3){ 0.0f, 0.0f, 0.0f };      // Camera looking at point
camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };          // Camera up vector (rotation towards target)
camera.fovy = 70.0f;                                // Camera field-of-view Y
camera.projection = CAMERA_PERSPECTIVE;             // Camera projection type
  emscripten_set_main_loop(UpdateDrawFrame, 0, 1);
  CloseWindow();

  return 0;
}


void UpdateDrawFrame(void){
	if (IsKeyDown(KEY_RIGHT)) ballPosition.x += 2.0f;
        if (IsKeyDown(KEY_LEFT)) ballPosition.x -= 2.0f;
        if (IsKeyDown(KEY_UP)) ballPosition.y -= 2.0f;
        if (IsKeyDown(KEY_DOWN)) ballPosition.y += 2.0f;
  BeginDrawing();
  	ClearBackground(RAYWHITE);
	DrawFPS(10, 10);
	BeginMode3D(camera);
	  DrawGrid(10, 3.0f);
	  Vector3 pos;
	  for(int i = 0; i < amount; i++){
	    pos = (Vector3){blocks[i].x, blocks[i].y, blocks[i].z};
	    //printf("drawing cube at: %d %d %d\n", blocks[i].x, blocks[i].y, blocks[i].z);
	    DrawCube(pos, 1, 1, 1, (Color){ 0, 121, 241, 255 });
	  }
	EndMode3D();
  EndDrawing();
  /*
  static int counter = 0;
  if(blocks == NULL){
    printf("%d: Blocks array is null.\n", counter++);
    return;
  }

  printf("amount: %d\n", amount);
  for(int i = 0; i < amount; i++){
	  printf("%d, %s\n", i, blocks[i].name);
  }
*/
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

