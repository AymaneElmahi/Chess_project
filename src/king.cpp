#include "king.hpp"
int King::isLegalMove(int StartCol, int StartLign, int EndCol, int EndLign)
{
    // check if the move is horizontal or vertical
    if (StartCol == EndCol || StartLign == EndLign)
    {
        // check if the move is one square
        if (abs(StartCol - EndCol) == 1 || abs(StartLign - EndLign) == 1)
        {
            return 1;
        }
        return 0;
    }

    // check if the move is diagonal
    if (abs(StartCol - EndCol) != abs(StartLign - EndLign))
    {
        // check if the move is one square
        if (abs(StartCol - EndCol) == 1 || abs(StartLign - EndLign) == 1)
        {
            return 1;
        }
    }
    return 0;
}