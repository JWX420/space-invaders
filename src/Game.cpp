#include <iostream>
#include <vector>
#include <unistd.h>     // pour usleep
#include <termios.h>    // pour lire les touches sans Entrée
#include <stdio.h>
#include "Game.hpp"

Game::Game() {
    width = 20;    // largeur de l'écran
    height = 10;   // hauteur de l'écran
    playerX = width / 2;
    // créer une ligne d'ennemis en haut
    enemyDirection = 1; // les ennemis commencent en allant vers la droite
    for (int i = 0; i < 5; i++) {
        Enemy e;
        e.x = 2 + i * 3; // espacement horizontal
        e.y = height - 1; // ligne du haut
        enemies.push_back(e);
    }
    running = true;
}

// fonction pour lire une touche sans Entrée
char getInput() {
    char buf = 0;
    struct termios old = {0};
    if (tcgetattr(0, &old) < 0) perror("tcgetattr()");
    old.c_lflag &= ~ICANON; // désactive le buffering
    old.c_lflag &= ~ECHO;   // ne pas afficher la touche
    old.c_cc[VMIN] = 0;
    old.c_cc[VTIME] = 0;
    if (tcsetattr(0, TCSANOW, &old) < 0) perror("tcsetattr ICANON");
    if (read(0, &buf, 1) < 0) {
        // pas de touche appuyée
    }
    old.c_lflag |= ICANON;
    old.c_lflag |= ECHO;
    if (tcsetattr(0, TCSADRAIN, &old) < 0) perror("tcsetattr ~ICANON");
    return buf;
}


void Game::run() {
    while (running) {
        render();

        char input = getInput();

        if (input == 'a' && playerX > 0) playerX--;
        if (input == 'd' && playerX < width - 1) playerX++;
        if (input == 't') shoot(); // tirer
        if (input == 'q') running = false;

        update();      // bouger les tirs
        usleep(100000); // 0.03 s → 3x plus fluide

    }
}



void Game::processInput() {
    char input;
    std::cin >> input;

    if (input == 'q') running = false; // quitter le jeu
    if (input == 'a' && playerX > 0) playerX--; // gauche
    if (input == 'd' && playerX < width-1) playerX++; // droite
    if (input == 't') {
    bulletsX.push_back(playerX);  // ajouter la position X du tir
    bulletsY.push_back(1);        // position Y initiale du tir (juste au-dessus du joueur)
}; // t d’espace pour tirer
}

void Game::update() {

    // --- Déplacement des ennemis ---
    bool mustGoDown = false;

    // vérifier si un ennemi touche le bord
    for (const auto& e : enemies) {
        if (e.x + enemyDirection < 0 || e.x + enemyDirection >= width) {
            mustGoDown = true;
            break;
        }
    }

    // appliquer le mouvement
    if (mustGoDown) {
        enemyDirection *= -1;   // changer de direction
        for (auto& e : enemies) e.y -= 1;
    } else {
        for (auto& e : enemies) e.x += enemyDirection;
    }


    // --- Mouvements des tirs ---
    for (int i = 0; i < bulletsY.size(); i++) {
        bulletsY[i]++;
    }

    // supprimer les tirs hors écran
    for (int i = bulletsY.size() - 1; i >= 0; i--) {
        if (bulletsY[i] >= height) {
            bulletsY.erase(bulletsY.begin() + i);
            bulletsX.erase(bulletsX.begin() + i);
        }
    }

    // vérifier collisions
    for (int i = bulletsY.size() - 1; i >= 0; i--) {
        for (int j = enemies.size() - 1; j >= 0; j--) {
            if (bulletsX[i] == enemies[j].x && bulletsY[i] == enemies[j].y) {
                enemies.erase(enemies.begin() + j);
                bulletsX.erase(bulletsX.begin() + i);
                bulletsY.erase(bulletsY.begin() + i);
                break;
            }
        }
    }
}




void Game::render() {
    system("clear"); // efface l'écran

    for (int y = height - 1; y >= 0; y--) {      // parcourir chaque ligne
        for (int x = 0; x < width; x++) {        // parcourir chaque colonne
            bool printed = false;

            // afficher les tirs
            for (int i = 0; i < bulletsX.size(); i++) {
                if (bulletsX[i] == x && bulletsY[i] == y) {
                    std::cout << '|';
                    printed = true;
                    break;
                }
            }

            // afficher les ennemis
            if (!printed) {
                for (const auto& e : enemies) {
                    if (e.x == x && e.y == y) {
                        std::cout << 'M'; // caractère pour un ennemi
                        printed = true;
                        break;
                    }
                }
            }

            // afficher le joueur
            if (!printed) {
                if (y == 0 && x == playerX)
                    std::cout << 'A';
                else
                    std::cout << '.';
            }
        }
        std::cout << std::endl; // passer à la ligne suivante
    }
}




void Game::shoot() {
    
    bulletsX.push_back(playerX); // le tir part de la position du joueur
    bulletsY.push_back(0);       // en haut de l’écran (ligne 0)
}
