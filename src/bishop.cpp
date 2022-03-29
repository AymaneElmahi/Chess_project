#include "bishop.hpp"

/**
 * @brief test if the move is legal for a bishop
 *
 * @param StartCol
 * @param StartLign
 * @param EndCol
 * @param EndLign
 * @return int return 1 if the move is legal, 0 otherwise
 */
int Bishop::isLegalMove(int StartCol, int StartLign, int EndCol, int EndLign)
{
    {
        // check if the move is diagonal
        if (abs(StartCol - EndCol) == abs(StartLign - EndLign))
        {
            return 1;
        }
        return 0;
    }
}