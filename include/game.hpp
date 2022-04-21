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
    Board getBoard();
    void get_move();
    int move(string startingPos, string endingPos);
    void affiche();
    Color getTurn();
    void setTurn(Color turn);

    int castle(string movement);
};