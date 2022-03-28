#include "knight.hpp"

int Knight::isLegalMove(int StartCol, int StartLign, int EndCol, int EndLign)
{
    // check if the move is diagonal
    if (abs(StartCol - EndCol) == abs(StartLign - EndLign))
    {
        return 1;
    }
    return 0;
}