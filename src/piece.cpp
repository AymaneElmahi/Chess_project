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

int Piece::get_hasMoved()
{
    return hasMoved;
}

int Piece::isLegalMove(int StartCol, int StartLign, int EndCol, int EndLign)
{
    UNUSED(StartLign);
    UNUSED(EndLign);
    UNUSED(EndCol);
    UNUSED(StartCol);
    return 1;
}

void Piece::setPosition(int Col, int Lign)
{
    position = Square(Col, Lign);
}

void Piece::setHasMoved(int hasMoved)
{
    this->hasMoved = hasMoved;
}

Piece *Piece::clone()
{
    return new Piece(color, name, position);
}

int Piece::canMove(int EndCol, int EndLign)
{
    return isLegalMove(position.get_column(), position.get_lign(), EndCol, EndLign);
}
