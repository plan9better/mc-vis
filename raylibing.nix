{ pkgs ? import <nixpkgs> {} }:

pkgs.mkShell {
  buildInputs = with pkgs; [
    gcc
    gdb
    gnumake
    cmake
    clang-tools
    valgrind
    pkg-config
    raylib

    # project specific
    emscripten
    cmake
    nodejs_20
  ];

  shellHook = ''
    export PS1='\[\e[38;5;160;1m\]<raylibing>\[\e[0m\]:\[\e[96;3m\]\u\[\e[0m\]@\w\[\e[92m\]\$\[\e[0m\] '
    echo "C development environment loaded"
    echo "Available tools: gcc, gdb, make, cmake, clang-tools, valgrind"
    gcc --version
  '';
}
