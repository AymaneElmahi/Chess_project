#pragma once
#include <string>
#include <vector>
#include <iostream>

class Square
{
public:
    /**
     * @brief Construct a new Square object
     *
     * @param col
     * @param lign
     */
    Square(int lign, int column) : lign(lign), column(column) {}

    /**
     * @brief Get the lign
     *
     * @return int
     */
    int get_lign();

    /**
     * @brief Get the column
     *
     * @return int
     */
    int get_column();

protected:
    int lign;   // lign of the square
    int column; // column of the square
};
