#pragma once
#include "piece.hpp"

class Queen : public Piece
{
public:
    /**
     * @brief Construct a new Queen object
     *
     * @param color
     * @param name
     * @param position
     */
    Queen(Color color, string name, Square position)
        : Piece(color, name, position) {}

    /**
     * @brief  check if the movement is legal for the queen
     *
     * @param StartCol
     * @param StartLign
     * @param EndCol
     * @param EndLign
     * @return int
     */
    virtual int isLegalMove(int StartCol, int StartLign, int EndCol, int EndLign);
};