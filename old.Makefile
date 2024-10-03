# Compiler and linker
EMCC      = emcc

SRC := $(wildcard src/*.c)
OUTPUT    = ./static/index.html
CFLAGS    = -Wall -I./raylib/src 
LDFLAGS   = -L./raylib/src -lraylib

# emcc
# EXPORTS   = -sEXPORTED_FUNCTIONS=_initBlocks -sEXPORTED_RUNTIME_METHODS=ccall,cwrap
EXPORTS   = -s NO_EXIT_RUNTIME=1 -sEXPORTED_FUNCTIONS="['_initBlocks','_addBlock','_main']" -sEXPORTED_RUNTIME_METHODS="['ccall','cwrap']"
SHELLFILE = --shell-file html_template/index.html
EMFLAGS   = -s USE_GLFW=3 -s FULL_ES2=1 -s GL_ENABLE_GET_PROC_ADDRESS=1


all:
	$(EMCC) $(SRC) $(CFLAGS) $(LDFLAGS) $(EMFLAGS) $(SHELLFILE) -o $(OUTPUT) $(EXPORTS)

clean:
	rm -f $(OUTPUT)
