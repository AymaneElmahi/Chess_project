#include "board.hpp"
#include "piece.hpp"
#include "bishop.hpp"
#include "knight.hpp"
#include "pawn.hpp"
#include "rook.hpp"
#include "king.hpp"
#include "queen.hpp"

class Game
{
protected:
    Board board;

public:
    Board getBoard();
    void get_move();
    int move(string startingPos, string endingPos);
    void affiche();
};