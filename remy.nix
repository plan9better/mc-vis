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
    go
    gopls
  ];

  shellHook = ''
    export PS1='\[\e[38;5;160;1m\]<remy>\[\e[0m\]:\[\e[96;3m\]\u\[\e[0m\]@\w\[\e[92m\]\$\[\e[0m\] '
    echo "C and Go development environment loaded"
    gcc --version
  '';
}
