#include "knight.hpp"

/**
 * @brief check if the move is legal for a knight
 *
 * @param StartCol
 * @param StartLign
 * @param EndCol
 * @param EndLign
 * @return int
 */
int Knight::isLegalMove(int StartCol, int StartLign, int EndCol, int EndLign)
{
    // check if the move is vertical or horizontal
    if (abs(StartCol - EndCol) == 1 && abs(StartLign - EndLign) == 2)
    {
        return 1;
    }
    if (abs(StartCol - EndCol) == 2 && abs(StartLign - EndLign) == 1)
    {
        return 1;
    }
    return 0;
}