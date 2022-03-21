#pragma once
#include <string>
#include <vector>
#include <iostream>

#include "macros.hpp"
#include "color.hpp"
#include "square.hpp"

using namespace std;

class Piece
{
public:
    Piece();
    Piece(Color color, string name, Square position)
        : color(color), name(name), position(position) {}
    void isLegalMove();
    Square get_position();
    Color get_color();
    void affiche();

protected:
    Color color;
    string name;
    Square position;
};
