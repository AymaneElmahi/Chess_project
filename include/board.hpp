#pragma once
#include <string>
#include <vector>
#include <iostream>
#include <sstream>

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
    /**
     * @brief Construct a new Board object
     *
     */
    Board();

    /**
     * @brief display the board
     *
     */
    void affiche();

    /**
     * @brief allocate memory for the board
     *
     */
    void allocMemBoard();

    /**
     * @brief put the piece on the board
     *
     * @param piece
     * @param startingPos
     */
    void putPiece(Piece *piece, Square startingPos);

    /**
     * @brief move the piece on the board
     *
     * @param col_orig
     * @param lign_orig
     * @param col_dest
     * @param lign_dest
     * @return int 1 if the move is legal, 0 otherwise
     */
    int move(int col_orig, int lign_orig, int col_dest, int lign_dest);

    /**
     * @brief check if the path is clear
     *
     * @param col_orig
     * @param lign_orig
     * @param col_dest
     * @param lign_dest
     * @return int 1 if the path is clear, 0 otherwise
     */
    int isPathClear(int col_orig, int lign_orig, int col_dest, int lign_dest);

    /**
     * @brief check if the path is clear for the bishop
     *
     * @param col_orig
     * @param lign_orig
     * @param col_dest
     * @param lign_dest
     * @return int 1 if the path is clear, 0 otherwise
     */
    int isPathClearBishop(int col_orig, int lign_orig, int col_dest, int lign_dest);

    /**
     * @brief check if the path is clear for the rook
     *
     * @param col_orig
     * @param lign_orig
     * @param col_dest
     * @param lign_dest
     * @return int 1 if the path is clear, 0 otherwise
     */
    int isPathClearRook(int col_orig, int lign_orig, int col_dest, int lign_dest);

    /**
     * @brief check if the path is clear from the queen
     *
     * @param col_orig
     * @param lign_orig
     * @param col_dest
     * @param lign_dest
     * @return int 1 if the path is clear, 0 otherwise
     */
    int isPathClearQueen(int col_orig, int lign_orig, int col_dest, int lign_dest);

    /**
     * @brief check if the path is clear for the pawn
     *
     * @param col_orig
     * @param lign_orig
     * @param col_dest
     * @param lign_dest
     * @return int 1 if the path is clear, 0 otherwise
     */
    int isPathClearPawn(int col_orig, int lign_orig, int col_dest, int lign_dest);

    /**
     * @brief check if the path is clear for a black pawn
     *
     * @param col_orig
     * @param lign_orig
     * @param col_dest
     * @param lign_dest
     * @return int 1 if the path is clear, 0 otherwise
     */
    int isPathClearPawnBlack(int col_orig, int lign_orig, int col_dest, int lign_dest);

    /**
     * @brief check if the path is clear for a white pawn
     *
     * @param col_orig
     * @param lign_orig
     * @param col_dest
     * @param lign_dest
     * @return int 1 if the path is clear, 0 otherwise
     */
    int isPathClearPawnWhite(int col_orig, int lign_orig, int col_dest, int lign_dest);

    /**
     * @brief check if the pawn can take
     *
     * @param col_orig
     * @param lign_orig
     * @param col_dest
     * @param lign_dest
     * @return int 1 if the taking is possible, 0 otherwise
     */
    int pawnIsTaking(int col_orig, int lign_orig, int col_dest, int lign_dest);

    /**
     * @brief   check if en passant is possible
     *
     * @param col_orig
     * @param lign_orig
     * @param col_dest
     * @param lign_dest
     * @return int 1 if the en passant is possible, 0 otherwise
     */
    int isEnPassant(int col_orig, int lign_orig, int col_dest, int lign_dest);

    /**
     * @brief check if the piece is attacking the opposite king
     *
     * @param piece
     * @return int  1 if the piece is attacking the opposite king, 0 otherwise
     */
    int isAttackingKing(Piece *piece);

    /**
     * @brief check if the king is in check
     *
     * @param color
     * @return int 1 if the king is in check, 0 otherwise
     */
    int isKingInCheck(Color color);

    /**
     * @brief check if the king will be in check after the move
     *
     * @param lign_orig
     * @param col_orig
     * @param lign_dest
     * @param col_dest
     * @return int 1 if the king will be in check, 0 otherwise
     */
    int kingWillBeInCheckAfterMove(int lign_orig, int col_orig, int lign_dest, int col_dest);

    /**
     * @brief check if the king will be in check while castling
     *
     * @param color
     * @param castlingType
     * @return int  1 if the king will be in check, 0 otherwise
     */
    int kingInCheckWhileCastling(Color color, int castlingType);

    /**
     * @brief check if the move is a promotion
     *
     * @param lign_orig
     * @param col_orig
     * @param lign_dest
     * @param col_dest
     * @return int 1 if the move is a promotion, 0 otherwise
     */
    int isPromotion(int lign_orig, int col_orig, int lign_dest, int col_dest);

    /**
     * @brief promote the pawn
     *
     * @param lign_orig
     * @param col_orig
     * @param lign_dest
     * @param col_dest
     * @return int 1 if the promotion is possible, 0 otherwise
     */
    int promotion(int lign_orig, int col_orig, int lign_dest, int col_dest);

    /**
     * @brief check if the destination square is accessible
     *
     * @param col_orig
     * @param lign_orig
     * @param col_dest
     * @param lign_dest
     * @return int 1 if the destination square is accessible, 0 otherwise
     */
    int destinationSquare(int col_orig, int lign_orig, int col_dest, int lign_dest);

    /**
     * @brief check if the king can castle
     *
     * @param color
     * @return int 1 if the king can castle, 0 otherwise
     */
    int canCastle(Color color);

    /**
     * @brief short castle
     *
     * @param color
     * @return int  1 if the short castle is possible, 0 otherwise
     */
    int shortCastling(Color color);

    /**
     * @brief long castle
     *
     * @param color
     * @return int  1 if the long castle is possible, 0 otherwise
     */
    int longCastling(Color color);

    /**
     * @brief check if the king will be in check after castling
     *
     * @param color
     * @param CastlingType
     * @return int  1 if the king will be in check, 0 otherwise
     */
    int KingInCheckAfterCastle(Color color, int CastlingType);

    /**
     * @brief check if it's checkmate
     *
     * @param color
     * @return int  1 if it's checkmate, 0 otherwise
     */
    int isCheckmate(Color color);

    /**
     * @brief check if it's stalemate
     *
     * @param color
     * @return int  1 if it's stalemate, 0 otherwise
     */
    int isStalemate(Color color);

    /**
     * @brief Get the Piece object
     *
     * @param lign
     * @param col
     * @return Piece*
     */
    Piece *getPiece(int lign, int col);

    /**
     * @brief Get the Board object
     *
     * @return Piece***
     */
    Piece ***getBoard();

    /**
     * @brief get the pgn of the piece
     *
     * @param name
     * @param view_pawn
     * @param view_color
     * @return string
     */
    string pgn_piece_name(string const name, bool view_pawn, bool view_color) const;

    /**
     * @brief get the canonical position of the board
     *
     * @return string
     */
    string canonicalPosition();

protected:
    Piece *board[8][8];           // board
    Piece *whitePieces[8];        // white pieces
    Piece *blackPieces[8];        // black pieces
    Piece *whitePawns[8];         // white pawns
    Piece *blackPawns[8];         // black pawns
    struct lastMove lastMove;     // last move
    int whiteKingCastled = 0;     // white king castled
    int blackKingCastled = 0;     // black king castled
    Square whiteKingPos = {0, 0}; // white king position
    Square blackKingPos = {0, 0}; // black king position
};