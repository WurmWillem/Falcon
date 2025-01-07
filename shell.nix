with import <nixpkgs> {}; 

pkgs.mkShell {
  name = "falcon";
  buildInputs = [stdenv ncurses cmake ninja ];

  shellHook = ''
    fish
  '';
}
