#pragma once
#include "piece.hpp"

class Rook : public Piece
{
public:
    Rook(Color color, string name, Square position)
        : Piece(color, name, position) {}
    virtual int isLegalMove(int StartCol, int StartLign, int EndCol, int EndLign);
};