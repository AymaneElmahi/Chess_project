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
    Square get_position();
    virtual int isLegalMove(int StartCol, int StartLign, int EndCol, int EndLign);
    string get_name();
    Color get_color();
    void affiche();

protected:
    Color color;
    string name;
    Square position;
};
