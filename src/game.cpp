#include "game.hpp"
#include "string.h"

void Game::move(string startingPos, string endingPos)
{

    int lign_orig = startingPos.substr(0, 1)[0] - 'a' + 1;
    int lign_dest = endingPos.substr(0, 1)[0] - 'a' + 1;
    int col_orig = stoi(startingPos.substr(1, 1));
    int col_dest = stoi(endingPos.substr(1, 1));

    board.move(lign_orig, col_orig, lign_dest, col_dest);
}

void Game::affiche()
{
    board.affiche();
}