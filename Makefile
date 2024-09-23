# Compiler and linker
EMCC      = emcc

SRC := $(wildcard src/*.c)
OUTPUT    = ./static/index.html
CFLAGS    = -Wall -I./raylib/src 
LDFLAGS   = -L./raylib/src -lraylib


# emcc
EXPORTS   = -s "EXPORTED_RUNTIME_METHODS=['ccall','cwrap']" 
LINKS     = --preload-file src/script.js@script.js --preload-file src/styles.css@styles.css
SHELLFILE = --shell-file html_template/index.html
EMFLAGS   = -s USE_GLFW=3 -s FULL_ES2=1 -s GL_ENABLE_GET_PROC_ADDRESS=1 -s NO_EXIT_RUNTIME=1

all:
	$(EMCC) $(SRC) $(CFLAGS) $(LDFLAGS) $(SFLAGS) $(EMFLAGS) $(LINKS) -o $(OUTPUT)

clean:
	rm -f $(OUTPUT)
