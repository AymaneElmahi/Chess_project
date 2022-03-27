#include "game.hpp"
#include "string.h"

void Game::move(string startingPos, string endingPos)
{

    int col_orig = startingPos.substr(0, 1)[0] - 'a';
    int col_dest = endingPos.substr(0, 1)[0] - 'a';
    int lign_orig = stoi(startingPos.substr(1, 1)) - 1; // board between 0 and 7
    int lign_dest = stoi(endingPos.substr(1, 1)) - 1;

    board.move(lign_orig, col_orig, lign_dest, col_dest);
}

void Game::affiche()
{
    board.affiche();
}
