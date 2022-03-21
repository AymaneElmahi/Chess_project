#pragma once
#include "piece.hpp"

class King : public Piece
{
public:
    King(Color color, string name, Square position)
        : Piece(color, name, position) {}
};