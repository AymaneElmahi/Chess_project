#pragma once
#include "piece.hpp"

class Queen : public Piece
{
public:
    Queen(Color color, string name, Square position)
        : Piece(color, name, position) {}

    virtual int isLegalMove(int StartCol, int StartLign, int EndCol, int EndLign);
};