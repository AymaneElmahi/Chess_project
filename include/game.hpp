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
    Color turn;

public:
    void setTurn(Color turn);
    void get_move();
    void move(string startingPos, string endingPos);
    void affiche();
};