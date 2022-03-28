#include "queen.hpp"

int Queen::isLegalMove(int StartCol, int StartLign, int EndCol, int EndLign)
{
    // check if the move is horizontal or vertical
    if (StartCol == EndCol || StartLign == EndLign)
    {
        return 1;
    }

    // check if the move is diagonal
    if (abs(StartCol - EndCol) == abs(StartLign - EndLign))
    {
        return 1;
    }
    return 0;
}