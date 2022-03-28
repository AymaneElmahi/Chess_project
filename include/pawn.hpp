#pragma once
#include "piece.hpp"

class Pawn : public Piece
{

public:
    Pawn(Color color, string name, Square position)
        : Piece(color, name, position) {}
    virtual int isLegalMove(int StartCol, int StartLign, int EndCol, int EndLign);
};