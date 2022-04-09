#include "game.hpp"
#include "string.h"

int Game::move(string startingPos, string endingPos)
{

    int col_orig = startingPos.substr(0, 1)[0] - 'a';
    int col_dest = endingPos.substr(0, 1)[0] - 'a';
    int lign_orig = stoi(startingPos.substr(1, 1)) - 1; // board between 0 and 7
    int lign_dest = stoi(endingPos.substr(1, 1)) - 1;

    if (board.getPiece(lign_orig, col_orig) != nullptr)
    {
        if (turn != board.getPiece(lign_orig, col_orig)->get_color())
        {
            cout << "It's not your turn!" << endl;
            return 0;
        }
    }

    if (board.move(col_orig, lign_orig, col_dest, lign_dest) == 1)
    {
        if (turn == White)
            turn = Black;
        else
            turn = White;
        return 1;
    }
    else
    {
        return 0;
    }
}

void Game::affiche()
{
    board.affiche();
}

Board Game::getBoard()
{
    return board;
}

void Game::setTurn(Color turn)
{
    this->turn = turn;
}

Color Game::getTurn()
{
    return turn;
}