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

struct lastMove
{
    Piece *piece = nullptr;
    int StartCol = 0;
    int StartLign = 0;
    int EndCol = 0;
    int EndLign = 0;
};

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
    int isEnPassant(int col_orig, int lign_orig, int col_dest, int lign_dest);
    int isAttackingKing(Piece *piece);
    int isKingInCheck(Color color);
    int kingWillBeInCheckAfterMove(int lign_orig, int col_orig, int lign_dest, int col_dest);

    int isPromotion(int lign_orig, int col_orig, int lign_dest, int col_dest);
    int promotion(int lign_orig, int col_orig, int lign_dest, int col_dest);
    int destinationSquare(int col_orig, int lign_orig, int col_dest, int lign_dest);

    int isCheckmate(Color color);
    int canCastle(Color color);
    int shortCastling(Color color);
    int longCastling(Color color);
    int KingInCheckAfterCastle(Color color, int CastlingType);

    Piece *getPiece(int lign, int col);
    Piece ***getBoard();

protected:
    Piece *board[8][8];
    Piece *whitePieces[8];
    Piece *blackPieces[8];
    Piece *whitePawns[8];
    Piece *blackPawns[8];
    struct lastMove lastMove;
    int whiteKingCastled = 0;
    int blackKingCastled = 0;
    Square whiteKingPos = {0, 0};
    Square blackKingPos = {0, 0};
};