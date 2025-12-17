#include "Game.hpp"

int main() {
    Game game;
#ifdef USE_SFML
    game.runSFML();
#else
    game.run();
#endif

    return 0;
}
