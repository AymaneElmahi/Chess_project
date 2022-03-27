#pragma once
#include <string>
#include <vector>
#include <iostream>

#include "macros.hpp"
#include "square.hpp"
#include "piece.hpp"
#include "bishop.hpp"
#include "knight.hpp"
#include "pawn.hpp"
#include "rook.hpp"
#include "king.hpp"
#include "queen.hpp"

using namespace std;

class Board
{

public:
    Board();
    void affiche();
    void allocMemBoard();
    void putPiece(Piece *piece, Square startingPos);
    void move(int lign_orig, int col_orig, int lign_dest, int col_dest);

    int isPathClear(int lign_orig, int col_orig, int lign_dest, int col_dest);
    int isPathClearBishop(int lign_orig, int col_orig, int lign_dest, int col_dest);
    int isPathClearRook(int lign_orig, int col_orig, int lign_dest, int col_dest);
    int isPathClearQueen(int lign_orig, int col_orig, int lign_dest, int col_dest);
    int isPathClearPawn(int lign_orig, int col_orig, int lign_dest, int col_dest);
    int isPathClearPawnBlack(int lign_orig, int col_orig, int lign_dest, int col_dest);
    int isPathClearPawnWhite(int lign_orig, int col_orig, int lign_dest, int col_dest);
    Piece *getPiece(int lign, int col);

protected:
    Piece *board[8][8];
    Piece *whitePieces[8];
    Piece *blackPieces[8];
    Piece *whitePawns[8];
    Piece *blackPawns[8];
};