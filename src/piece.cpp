#include "piece.hpp"

void Piece::affiche()
{
    cout << name;
}

Square Piece::get_position()
{
    return position;
}

string Piece::get_name()
{
    return name;
}

Color Piece::get_color()
{
    return color;
}

/**
 * @brief
 *
 * @param StartCol
 * @param StartLign
 * @param EndCol
 * @param EndLign
 * @return int 1 if the move is legal, 0 otherwise
 */
int Piece::isLegalMove(int StartCol, int StartLign, int EndCol, int EndLign)
{
    // check if the piece is a rook
    if (name == " \u2656 " || name == " \u265C ")
    {
        // check if the move is horizontal or vertical
        if (StartCol == EndCol || StartLign == EndLign)
        {
            return 1;
        }
        return 0;
    }

    // check if the piece is a bishop
    if (name == " \u2657 " || name == " \u265D ")
    {
        // check if the move is diagonal
        if (abs(StartCol - EndCol) == abs(StartLign - EndLign))
        {
            return 1;
        }
        return 0;
    }

    // check if the piece is a queen
    if (name == " \u2655 " || name == " \u265B ")
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

    // check if the piece is a king
    if (name == " \u2654 " || name == " \u265A ")
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

    // check if the piece is a knight
    if (name == " \u2658 " || name == " \u265E ")
    {
        // check if the move is diagonal
        if (abs(StartCol - EndCol) == abs(StartLign - EndLign))
        {
            return 1;
        }
        return 0;
    }

    // check if the piece is a pawn
    if (name == " \u2659 " || name == " \u265F ")
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
    return 1;
}

void Piece::setPosition(int Col, int Lign)
{
    position = Square(Col, Lign);
}
