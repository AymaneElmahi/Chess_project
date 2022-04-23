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
    /**
     * @brief Construct a new Piece object
     *
     */
    Piece();

    /**
     * @brief Construct a new Piece object
     *
     * @param color
     * @param name
     * @param position
     */
    Piece(Color color, string name, Square position)
        : color(color), name(name), position(position) {}

    /**
     * @brief Destroy the Piece object
     *
     */
    virtual ~Piece() {}

    /**
     * @brief  check if the movement is legal for the piece
     *
     * @param StartCol
     * @param StartLign
     * @param EndCol
     * @param EndLign
     * @return int
     */
    virtual int isLegalMove(int StartCol, int StartLign, int EndCol, int EndLign);

    /**
     * @brief Set the Position
     *
     * @param Col
     * @param Lign
     */
    void setPosition(int Col, int Lign);

    /**
     * @brief Set the Has Moved flag
     *
     * @param hasMoved
     */
    void setHasMoved(int hasMoved);

    /**
     * @brief Get the color of the piece
     *
     * @return Color
     */
    Color get_color();

    /**
     * @brief Get the name of the piece
     *
     * @return string
     */
    string get_name();

    /**
     * @brief Get the position of the piece
     *
     * @return Square
     */
    Square get_position();

    /**
     * @brief Get the hasMoved flag
     *
     * @return int
     */
    int get_hasMoved();

    /**
     * @brief check if the piece can move to the square
     *
     * @param EndCol
     * @param EndLign
     * @return int
     */
    virtual int canMove(int EndCol, int EndLign);

    /**
     * @brief  print the piece
     *
     */
    void affiche();

    /**
     * @brief clone the piece
     *
     * @return Piece*
     */
    Piece *clone();

protected:
    Color color;      // Color of the piece
    string name;      // Name of the piece
    Square position;  // Position of the piece
    int hasMoved = 0; // Has the piece moved ?
};
