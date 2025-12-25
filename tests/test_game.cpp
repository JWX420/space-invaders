#include <catch2/catch_test_macros.hpp>
#include "Game.hpp"

/**
 * \brief Tests minimaux (smoke tests) pour vérifier que les fonctions de base
 *        s'exécutent sans crash.
 *
 * \note Pour des tests plus fins (score, ennemis, tirs...), on ajoutera
 *       des accesseurs const dans Game dans un jalon suivant.
 */
TEST_CASE("Initialisation du jeu", "[game]") {
    Game g;
    SUCCEED("Le constructeur Game() ne doit pas crasher.");
}

TEST_CASE("Mise à jour du jeu", "[game]") {
    Game g;
    g.update();
    SUCCEED("update() ne doit pas crasher sur un état initial.");
}
