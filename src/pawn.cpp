#include "pawn.hpp"

int Pawn::isLegalMove(int StartCol, int StartLign, int EndCol, int EndLign)
{
    // check if the pawn is going up

    if (color == White)
    {
        if (EndLign <= StartLign || EndCol > StartCol + 1 || EndCol < StartCol - 1)
            return 0;
    }
    else
    {
        if (EndLign >= StartLign || EndCol > StartCol + 1 || EndCol < StartCol - 1)
            return 0;
    }
    // check if it's the first move
    if (StartLign != 1 && StartLign != 6)
    {
        // check if the pawn is moving 2 squares
        if (abs(StartLign - EndLign) == 2)
        {
            return 0;
        }
    }
    // pawns can go up by one or two squares at a time
    if (abs(EndLign - StartLign) != 1 && abs(EndLign - StartLign) != 2)
    {
        return 0;
    }

    // check if the move is diagonal
    if (StartCol != EndCol)
    {
        return 2;
    }
    return 1;
}
