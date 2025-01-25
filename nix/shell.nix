{
  pkgs ? import <nixpkgs> { },
  baseShell,
}:

pkgs.mkShell.override { inherit (baseShell) stdenv; } {
  # issue building std module with FORITFY_SOURCE
  # see: https://github.com/llvm/llvm-project/issues/121709
  hardeningDisable = [
    "fortify"
  ];

  inputsFrom = [
    # base shell provides cmake, ninja, and clang (w/ libc++)
    # see: https://github.com/mtpham99/nixshell-cpp23-stdmodule
    baseShell
  ];

  nativeBuildInputs = [
    pkgs.ccache
    pkgs.doctest
  ];

  shellHook = ''
    export CMAKE_CXX_COMPILER_LAUNCHER="${pkgs.ccache}/bin/ccache"
    export CMAKE_EXPORT_COMPILE_COMMANDS="ON"
    export CMAKE_CXX_FLAGS="-Wall -Wextra -Wpedantic -Werror -Wconversion -Wshadow"
  '';
}
