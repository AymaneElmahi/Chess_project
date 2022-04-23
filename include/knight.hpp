#pragma once
#include "piece.hpp"

class Knight : public Piece
{
public:
    /**
     * @brief Construct a new Knight object
     *
     * @param color
     * @param name
     * @param position
     */
    Knight(Color color, string name, Square position)
        : Piece(color, name, position) {}

    /**
     * @brief  check if the movement is legal for the knight
     *
     * @param StartCol
     * @param StartLign
     * @param EndCol
     * @param EndLign
     * @return int
     */
    virtual int isLegalMove(int StartCol, int StartLign, int EndCol, int EndLign);
};