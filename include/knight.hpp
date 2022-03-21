#pragma once
#include "piece.hpp"

class Knight : public Piece
{
public:
    Knight(Color color, string name, Square position)
        : Piece(color, name, position) {}
};