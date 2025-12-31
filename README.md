# Space Invaders (C++)

Projet de Space Invaders en C++ (M2 Ingénierie Mathématiques – Sorbonne Université) avec :
- une version **console** (rendu ASCII)
- une version **graphique** via **SFML**

## Fonctionnalités
- Déplacement du joueur, tirs, collisions
- Score, vies, niveaux
- Niveaux “boss” (tous les 5 niveaux)
- Version SFML avec :
  - Fond étoilé animé
  - Mise à l’échelle (letterboxing) avec `sf::View`
  - Feedback visuel (flash + secousse) lors des dégâts
  - Explosions animées
  - HUD : texte, icônes de vies, barre de vie du boss

## Prérequis

### Linux / WSL (Debian 11)
Installer les dépendances :
- sudo apt update
- sudo apt install -y build-essential cmake pkg-config libsfml-dev doxygen graphviz x11-apps

### Windows 11 + WSLg (affichage graphique)
Sous Windows 11, l’affichage des fenêtres SFML se fait via WSLg.

Mise à jour WSL (PowerShell admin) :
- wsl --update
- wsl --shutdown

Test GUI (dans WSL) :
- xeyes

Dépannage (WSLg) :
- `DISPLAY` doit généralement être `:0`
- ne pas utiliser `LIBGL_ALWAYS_INDIRECT=1` (peut provoquer des erreurs GLX avec SFML)

## Compilation
À la racine du projet :
- cmake -S . -B build
- cmake --build build -j1

Remarque : `-j1` est volontairement conservateur (plus stable sur certaines configs WSL). Si tout va bien, tu peux utiliser `-j` pour compiler plus vite.

## Lancement

Version console :
- ./build/space_invaders_console

Version SFML :
- ./build/space_invaders_sfml

## Contrôles (SFML)
- Déplacement : `A` / `D` ou flèches gauche/droite
- Tir : `Espace`
- Quitter : `Échap`

## Tests (Catch2)
- cd build
- ctest --output-on-failure

## Documentation (Doxygen)
- doxygen docs/Doxyfile  
Résultat : `docs/html/index.html`

## Organisation du projet
- `include/` : headers (API du jeu)
- `src/` : logique + exécutables console/SFML
- `assets/` : ressources (fonts, textures, etc.)
- `tests/` : tests unitaires Catch2
- `docs/` : configuration Doxygen
