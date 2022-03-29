#pragma once
#include "piece.hpp"

class Bishop : public Piece
{
public:
    Bishop(Color color, string name, Square position)
        : Piece(color, name, position) {}

    virtual int isLegalMove(int StartCol, int StartLign, int EndCol, int EndLign);
};