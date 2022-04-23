#pragma once
#include "piece.hpp"

class Bishop : public Piece
{
public:
    /**
     * @brief Construct a new Bishop object
     *
     * @param color
     * @param name
     * @param position
     */
    Bishop(Color color, string name, Square position)
        : Piece(color, name, position) {}

    /**
     * @brief check if the movement is legal for the bishop
     *
     * @param StartCol
     * @param StartLign
     * @param EndCol
     * @param EndLign
     * @return int
     */
    virtual int isLegalMove(int StartCol, int StartLign, int EndCol, int EndLign);
};