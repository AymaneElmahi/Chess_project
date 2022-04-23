#pragma once
#include "piece.hpp"

class Pawn : public Piece
{

public:
    /**
     * @brief Construct a new Pawn object
     *
     * @param color
     * @param name
     * @param position
     */
    Pawn(Color color, string name, Square position)
        : Piece(color, name, position) {}

    /**
     * @brief  check if the movement is legal for the pawn
     *
     * @param StartCol
     * @param StartLign
     * @param EndCol
     * @param EndLign
     * @return int
     */
    virtual int isLegalMove(int StartCol, int StartLign, int EndCol, int EndLign);
};