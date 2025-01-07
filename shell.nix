with import <nixpkgs> {};
  pkgs.mkShell {
    name = "falcon";
    buildInputs = [stdenv ncurses cmake ninja];

    shellHook = ''
      export CMAKE_GENERATOR="Ninja"
      fish
    '';
    # cmake -G Ninja -DCMAKE_MAKE_PROGRAM=$(which ninja) /home/wurm/Dev/Falcon
    # ninja && ./falcon main.cpp

    # cmake -G Ninja -DCMAKE_MAKE_PROGRAM=$(which ninja) && ninja && ./falcon main.cpp
  }
