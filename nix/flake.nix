{
  description = "wrapper type flake";

  inputs = {
    nixpkgs.url = "github:NixOS/nixpkgs/nixpkgs-unstable";

    cpp23-importstd-shell = {
      url = "github:mtpham99/nixshell-cpp23-stdmodule?dir=nix";
      inputs.nixpkgs.follows = "nixpkgs";
    };
  };

  outputs = {self, nixpkgs, cpp23-importstd-shell} @ inputs :
  let
    system = "x86_64-linux";
    pkgs = (import nixpkgs { inherit system; });
  in
  {
    # development shell
    devShells."${system}".default = import ./shell.nix {
      inherit pkgs;
      baseShell = inputs.cpp23-importstd-shell.devShells."${system}".default;
    };
  };
}
