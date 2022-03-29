#include "game.hpp"
#include "string.h"

void Game::move(string startingPos, string endingPos)
{

    int col_orig = startingPos.substr(0, 1)[0] - 'a';
    int col_dest = endingPos.substr(0, 1)[0] - 'a';
    int lign_orig = stoi(startingPos.substr(1, 1)) - 1; // board between 0 and 7
    int lign_dest = stoi(endingPos.substr(1, 1)) - 1;

    if (board.getPiece(lign_orig, col_orig)->get_color() != turn)
    {
        cout << "You can't move your opponent's piece" << endl;
        return;
    }

    // alternate turns
    if (turn == White)
    {
        turn = Black;
    }
    else
    {
        turn = White;
    }

    board.move(col_orig, lign_orig, col_dest, lign_dest);
}

void Game::affiche()
{
    board.affiche();
}

void Game::setTurn(Color turn)
{
    this->turn = turn;
}
