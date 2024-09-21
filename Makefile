# Compiler and linker
EMCC      = emcc

SRC := $(wildcard src/*.c)
OUTPUT    = ./static/index.html
CFLAGS    = -Wall -I./load.h -I./raylib/src
LDFLAGS   = -L./raylib/src -lraylib
EMFLAGS   = -s USE_GLFW=3 -s FULL_ES2=1 -s GL_ENABLE_GET_PROC_ADDRESS=1
all:
	$(EMCC) $(SRC) $(CFLAGS) $(LDFLAGS) $(EMFLAGS) -o $(OUTPUT)

clean:
	rm -f $(OUTPUT)
