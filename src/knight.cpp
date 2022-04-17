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
    // test the 8 squares the knight can move to
    if (((EndCol == StartCol + 1) && (EndLign == StartLign + 2)) ||
        ((EndCol == StartCol + 1) && (EndLign == StartLign - 2)) ||
        ((EndCol == StartCol - 1) && (EndLign == StartLign + 2)) ||
        ((EndCol == StartCol - 1) && (EndLign == StartLign - 2)) ||
        ((EndCol == StartCol + 2) && (EndLign == StartLign + 1)) ||
        ((EndCol == StartCol + 2) && (EndLign == StartLign - 1)) ||
        ((EndCol == StartCol - 2) && (EndLign == StartLign + 1)) ||
        ((EndCol == StartCol - 2) && (EndLign == StartLign - 1)))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}