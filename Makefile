build:
	emcc main.c load.c -Wall -o index.html -s USE_GLFW=3 -s FULL_ES2=1 -s GL_ENABLE_GET_PROC_ADDRESS=1 -I./loader.h -L./raylib/src -lraylib -I./raylib/src

