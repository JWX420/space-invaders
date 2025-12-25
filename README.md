# Space Invaders (C++)

Projet Space Invaders en C++ avec :
- une version console (ASCII)
- une version graphique SFML

## Compilation

cmake -S . -B build
cmake --build build -j1

## Lancement

### Version console
./build/space_invaders_console

### Version SFML
./build/space_invaders_sfml

## Contrôles (SFML)
- Déplacement : A/D ou flèches gauche/droite
- Tir : Espace
- Quitter : Échap

## Tests (Catch2)
cd build
ctest --output-on-failure

## Documentation (Doxygen)
doxygen docs/Doxyfile

La documentation HTML est générée dans `docs/html/`.