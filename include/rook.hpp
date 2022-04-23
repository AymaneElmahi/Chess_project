#pragma once
#include "piece.hpp"

class Rook : public Piece
{
public:
    /**
     * @brief Construct a new Rook object
     *
     * @param color
     * @param name
     * @param position
     */
    Rook(Color color, string name, Square position)
        : Piece(color, name, position) {}

    /**
     * @brief   check if the movement is legal for the rook
     *
     * @param StartCol
     * @param StartLign
     * @param EndCol
     * @param EndLign
     * @return int
     */
    virtual int isLegalMove(int StartCol, int StartLign, int EndCol, int EndLign);
};