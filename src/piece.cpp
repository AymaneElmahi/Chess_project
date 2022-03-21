#include "piece.hpp"

void Piece::affiche()
{
    cout << name;
}

Square Piece::get_position()
{
    return position;
}