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
    void setHasMoved(int hasMoved);

    Color get_color();
    string get_name();
    Square get_position();
    int get_hasMoved();
    virtual int canMove(int StartCol, int StartLign);

    void affiche();
    Piece *clone();

protected:
    Color color;
    string name;
    Square position;
    int hasMoved = 0;
};
