#pragma once
#include "piece.hpp"

class King : public Piece
{
public:

    /**
     * @brief Construct a new King object
     *
     * @param color
     * @param name
     * @param position
     */
    King(Color color, string name, Square position)
        : Piece(color, name, position) {}

    /**
     * @brief  check if the movement is legal for the king
     * 
     * @param StartCol 
     * @param StartLign 
     * @param EndCol 
     * @param EndLign 
     * @return int 
     */
    virtual int isLegalMove(int StartCol, int StartLign, int EndCol, int EndLign);
};