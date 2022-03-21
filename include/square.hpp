#pragma once
#include <string>
#include <vector>
#include <iostream>

class Square
{
public:
    Square(int lign, int column) : lign(lign), column(column) {}
    int get_lign();
    int get_column();

protected:
    int lign;
    int column;
};
