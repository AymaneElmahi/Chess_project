#include "pawn.hpp"

int Pawn::isLegalMove(int StartCol, int StartLign, int EndCol, int EndLign)
{
    // pawns can go up by one or two squares at a time
    if (abs(EndLign - StartLign) != 1 && abs(EndLign - StartLign) != 2)
    {
        return 0;
    }

    // check if the move is vertical
    if (StartCol == EndCol)
    {
        return 1;
    }

    return 0;
}