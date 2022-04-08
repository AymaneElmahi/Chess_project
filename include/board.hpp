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
    int move(int col_orig, int lign_orig, int col_dest, int lign_dest);

    int isPathClear(int col_orig, int lign_orig, int col_dest, int lign_dest);
    int isPathClearBishop(int col_orig, int lign_orig, int col_dest, int lign_dest);
    int isPathClearRook(int col_orig, int lign_orig, int col_dest, int lign_dest);
    int isPathClearQueen(int col_orig, int lign_orig, int col_dest, int lign_dest);
    int isPathClearPawn(int col_orig, int lign_orig, int col_dest, int lign_dest);
    int isPathClearPawnBlack(int col_orig, int lign_orig, int col_dest, int lign_dest);
    int isPathClearPawnWhite(int col_orig, int lign_orig, int col_dest, int lign_dest);

    int pawnIsTaking(int col_orig, int lign_orig, int col_dest, int lign_dest);

    int destinationSquare(int col_orig, int lign_orig, int col_dest, int lign_dest);

    Piece *getPiece(int lign, int col);
    // void setTurn(Color turn);
    // Color getTurn();

protected:
    Piece *board[8][8];
    Piece *whitePieces[8];
    Piece *blackPieces[8];
    Piece *whitePawns[8];
    Piece *blackPawns[8];
};