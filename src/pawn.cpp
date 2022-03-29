#include "pawn.hpp"

int Pawn::isLegalMove(int StartCol, int StartLign, int EndCol, int EndLign)
{
    // check if it's the first move
    if (StartLign != 1 && StartLign != 6)
    {
        // check if the pawn is moving 2 squares
        if (abs(StartLign - EndLign) == 2)
        {
            cout << "Pawn can only move 2 squares at the beginning" << endl;
            return 0;
        }
    }
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
