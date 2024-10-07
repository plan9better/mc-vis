CC := emcc
CFLAGS := -Wall -I./raylib/src
LDFLAGS := -L./raylib/src -lraylib

OUTPUT := -o static/index.html
SRC := src/main.c
SHELLFILE := --shell-file html_template/shell.html
EXPORTS := -s NO_EXIT_RUNTIME=1 -s "EXPORTED_RUNTIME_METHODS=['ccall']" -s USE_GLFW=3 -sGL_ENABLE_GET_PROC_ADDRESS

build: 
	$(CC) $(CFLAGS) $(LDFLAGS) $(OUTPUT) $(SRC) $(SHELLFILE) $(EXPORTS)
