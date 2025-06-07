{
  description = "A Nix-flake-based C + SDL2 development environment";

  inputs = {
    nixpkgs.url = "github:nixos/nixpkgs/nixos-25.05";
  };

  outputs = { self, nixpkgs, ...}:
  let
    system = "x86_64-linux";
  in {
    devShells."${system}".default =
    let
      pkgs = import nixpkgs { inherit system; };
    in pkgs.mkShell.override { stdenv = pkgs.llvmPackages_20.stdenv; }
    {
      nativeBuildInputs = with pkgs; [
        pkg-config
      ];

      buildInputs = with pkgs; [
        meson
        ninja
        (SDL2.overrideAttrs (
          old: {
            dontDisableStatic = true;
            configureFlags = (old.configureFlags or []) ++ [ "--enable-static" "--disable-shared" ];
          }
        ))
        zsh
      ];

      shellHook = ''
        exec zsh
      '';

      PKG_CONFIG_ALL_STATIC = "1";
    };
  };
}
