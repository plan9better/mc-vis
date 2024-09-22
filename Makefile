# Compiler and linker
EMCC      = emcc

SRC := $(wildcard src/*.c)
OUTPUT    = ./static/index.html
# CFLAGS    = -Wall -I./load.h -I./raylib/src
# CFLAGS    = -Wall -I./src/raylib/src -I/nix/store/7b7r6k48n0pqrwm0dxsyz34cnhkyh7v6-emscripten-3.1.64/share/emscripten/cache/sysroot/include/
CFLAGS    = -Wall -I./src/raylib/src 
SFLAGS    = -s EXPORTED_FUNCTIONS="['_initBlocks', '_addBlock']" -s MODULARIZE=1 -s ENVIRONMENT=web -s EXPORT_NAME=MyModule
LDFLAGS   = -L./src/raylib/src -lraylib
EMFLAGS   = -s USE_GLFW=3 -s FULL_ES2=1 -s GL_ENABLE_GET_PROC_ADDRESS=1
all:
	$(EMCC) $(SRC) $(CFLAGS) $(LDFLAGS) $(SFLAGS) $(EMFLAGS) -o $(OUTPUT)

clean:
	rm -f $(OUTPUT)
