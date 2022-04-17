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
    // destructor
    virtual ~Piece()
    {
        cout << "Piece destructor called" << endl;
    }

    virtual int isLegalMove(int StartCol, int StartLign, int EndCol, int EndLign);
    void setPosition(int Col, int Lign);

    Color get_color();
    string get_name();
    Square get_position();

    void affiche();
    Piece *clone();

protected:
    Color color;
    string name;
    Square position;
};
