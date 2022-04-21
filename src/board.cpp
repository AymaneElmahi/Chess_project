#include "board.hpp"
#include "piece.hpp"
#include "macros.hpp"

/**
 * @brief set board cases to nullptr
 *
 */
void Board::allocMemBoard()
{
    for (int i = 0; i < NBCOL; i++)
    {
        for (int j = 0; j < NBLIGN; j++)
        {
            board[i][j] = nullptr;
        }
    }
}

/**
 * @brief put a piece on the board (used to initialize the board)
 *
 * @param piece piece to put on the board
 * @param position position of the piece
 */
void Board::putPiece(Piece *piece, Square position)
{
    board[position.get_lign()][position.get_column()] = piece;
}

/**
 * @brief move a piece on the board
 *
 * @param lign_orig the lign of the piece to move
 * @param col_orig the column of the piece to move
 * @param lign_dest the lign of the destination
 * @param col_dest the column of the destination
 * @return int 1 if the move is possible, 0 otherwise
 */
int Board::move(int col_orig, int lign_orig, int col_dest, int lign_dest)
{
    // check if the move is within the Board
    if (lign_orig < 0 ||
        lign_orig > 7 ||
        lign_dest < 0 ||
        lign_dest > 7 ||
        col_orig < 0 ||
        col_orig > 7 ||
        col_dest < 0 ||
        col_dest > 7)
    {
        cout << "Move is not within the board" << endl;
        return 0;
    }

    // check if there is a piece in the square
    if (board[lign_orig][col_orig] == nullptr)
    {
        cout << "No piece at this position" << endl;
        return 0;
    }

    // check if the move is legal
    if ((board[lign_orig][col_orig]->isLegalMove(col_orig, lign_orig, col_dest, lign_dest) == 0))
    {
        cout << "Move is not legal" << endl;
        return 0;
    }
    else if (board[lign_orig][col_orig]->isLegalMove(col_orig, lign_orig, col_dest, lign_dest) == 2)
    {
        if (isEnPassant(col_orig, lign_orig, col_dest, lign_dest) == 1)
        {
            // test if the king will be in check after the move, if yes, ask the player to move the king out of the check
            if (kingWillBeInCheckAfterMove(lign_orig, col_orig, lign_dest, col_dest))
            {
                cout << "The king is in check, or will be in check after this move, please move the king out of the check" << endl;
                return 0;
            }

            board[lign_dest][col_dest] = board[lign_orig][col_orig];
            board[lign_orig][col_orig] = nullptr;
            board[lastMove.EndLign][lastMove.EndCol] = nullptr;
            board[lign_dest][col_dest]->setPosition(col_dest, lign_dest);

            lastMove.piece = board[lign_orig][col_orig];
            lastMove.StartCol = col_orig;
            lastMove.StartLign = lign_orig;
            lastMove.EndCol = col_dest;
            lastMove.EndLign = lign_dest;

            Color otherColor;
            if (board[lign_dest][col_dest]->get_color() == White)
            {
                otherColor = Black;
            }
            else
            {
                otherColor = White;
            }
            if (isKingInCheck(otherColor))
            {
                cout << "Check !" << endl;
            }

            return 1;
        }
        if (pawnIsTaking(col_orig, lign_orig, col_dest, lign_dest) == 1)
        {
            // test if the king will be in check after the move, if yes, ask the player to move the king out of the check
            if (kingWillBeInCheckAfterMove(lign_orig, col_orig, lign_dest, col_dest))
            {
                cout << "The king is in check, or will be in check after this move, please move the king out of the check" << endl;
                return 0;
            }
            if (isPromotion(lign_orig, col_orig, lign_dest, col_dest) == 1)
            {
                promotion(lign_orig, col_orig, lign_dest, col_dest);
                return 1;
            }
            board[lign_dest][col_dest] = board[lign_orig][col_orig];
            board[lign_orig][col_orig] = nullptr;

            // save last move
            lastMove.piece = board[lign_orig][col_orig];
            lastMove.StartCol = col_orig;
            lastMove.StartLign = lign_orig;
            lastMove.EndCol = col_dest;
            lastMove.EndLign = lign_dest;

            Color otherColor;
            if (board[lign_dest][col_dest]->get_color() == White)
            {
                otherColor = Black;
            }
            else
            {
                otherColor = White;
            }
            if (isKingInCheck(otherColor))
            {
                cout << "Check !" << endl;
            }

            return 1;
        }
        else
        {
            cout << "Pawn is not taking" << endl;
            return 0;
        }
    }

    // check if the path is clear
    if (isPathClear(col_orig, lign_orig, col_dest, lign_dest) == 0)
    {
        cout << "Path is not clear" << endl;
        return 0;
    }

    // test if the king will be in check after the move, if yes, ask the player to move the king out of the check
    if (kingWillBeInCheckAfterMove(lign_orig, col_orig, lign_dest, col_dest))
    {
        cout << "The king is in check, or will be in check after this move, please move the king out of the check" << endl;
        return 0;
    }

    // check if the move is a promotion
    if (isPromotion(lign_orig, col_orig, lign_dest, col_dest) == 1)
    {
        promotion(lign_orig, col_orig, lign_dest, col_dest);
        return 1;
    }

    // save the move into last move
    lastMove.piece = board[lign_orig][col_orig];
    lastMove.StartCol = col_orig;
    lastMove.StartLign = lign_orig;
    lastMove.EndCol = col_dest;
    lastMove.EndLign = lign_dest;

    board[lign_dest][col_dest] = board[lign_orig][col_orig];
    board[lign_orig][col_orig] = nullptr;
    board[lign_dest][col_dest]->setPosition(lign_dest, col_dest);

    // if king is moved, update the king position
    if (board[lign_dest][col_dest]->get_name() == " \u2654 ")
    {
        whiteKingPos = {lign_dest, col_dest};
        board[lign_dest][col_dest]->setHasMoved(1);
    }
    if (board[lign_dest][col_dest]->get_name() == " \u265A ")
    {
        blackKingPos = {lign_dest, col_dest};
        board[lign_dest][col_dest]->setHasMoved(1);
    }

    // test if the king is in check now, if yes, ask the player to move the king out of the check
    // get the other color
    Color otherColor;
    if (board[lign_dest][col_dest]->get_color() == White)
    {
        otherColor = Black;
    }
    else
    {
        otherColor = White;
    }
    if (isKingInCheck(otherColor))
    {
        cout << "Check !" << endl;
    }

    return 1;
}

Board::Board()
{

    allocMemBoard(); // allocate memory for the board
    // Constructeur (Couleur,nom_affiché, case)
    whitePieces[0] = new Rook(White, " \u2656 ", Square(0, 0));
    whitePieces[1] = new Knight(White, " \u2658 ", Square(0, 1));
    whitePieces[2] = new Bishop(White, " \u2657 ", Square(0, 2));
    whitePieces[3] = new Queen(White, " \u2655 ", Square(0, 3));
    whitePieces[4] = new King(White, " \u2654 ", Square(0, 4));
    whitePieces[5] = new Bishop(White, " \u2657 ", Square(0, 5));
    whitePieces[6] = new Knight(White, " \u2658 ", Square(0, 6));
    whitePieces[7] = new Rook(White, " \u2656 ", Square(0, 7));
    blackPieces[0] = new Rook(Black, " \u265C ", Square(7, 0));
    blackPieces[1] = new Knight(Black, " \u265E ", Square(7, 1));
    blackPieces[2] = new Bishop(Black, " \u265D ", Square(7, 2));
    blackPieces[3] = new Queen(Black, " \u265B ", Square(7, 3));
    blackPieces[4] = new King(Black, " \u265A ", Square(7, 4));
    blackPieces[5] = new Bishop(Black, " \u265D ", Square(7, 5));
    blackPieces[6] = new Knight(Black, " \u265E ", Square(7, 6));
    blackPieces[7] = new Rook(Black, " \u265C ", Square(7, 7));

    // save the kings positions
    whiteKingPos = whitePieces[4]->get_position();
    blackKingPos = blackPieces[4]->get_position();

    // allocation des Pawns
    for (unsigned char i(0); i < NBCOL; i++)
    {
        whitePawns[i] = new Pawn(White, " \u2659 ", Square(1, i));
        blackPawns[i] = new Pawn(Black, " \u265F ", Square(6, i));
    }

    for (unsigned char i(0); i < NBCOL; i++)
    {
        putPiece(whitePieces[i], whitePieces[i]->get_position());
        putPiece(blackPieces[i], blackPieces[i]->get_position());
        putPiece(whitePawns[i], whitePawns[i]->get_position());
        putPiece(blackPawns[i], blackPawns[i]->get_position());
    }
}

void Board::affiche()
{
    string space5 = string(5, ' ');
    cout << endl;
    cout << "     a     b     c     d     e     f     g     h    " << endl;
    cout << "  +-----+-----+-----+-----+-----+-----+-----+-----+" << endl;
    for (int i(NBLIGN - 1); i >= 0; i--)
    {
        cout << i + 1 << " "; // numérotation ligne dans affichage
        for (int j(0); j < NBCOL; j++)
        {
            cout << "|";
            if (board[i][j])
            {
                board[i][j]->affiche();
                cout << "\u0020"
                     << " ";
            }
            else
                cout << space5; // 2 ascii spaces
        }
        cout << "|\n  +-----+-----+-----+-----+-----+-----+-----+-----+";
        cout << endl;
    }
}

Piece *Board::getPiece(int lign, int col)
{
    return board[lign][col];
}

/**
 * @brief check is the path is clear
 *
 * @param lign_orig
 * @param col_orig
 * @param lign_dest
 * @param col_dest
 * @return int return 1 if the path is clear, 0 if not
 */

int Board::isPathClearBishop(int col_orig, int lign_orig, int col_dest, int lign_dest)
{
    int lign_diff = lign_dest - lign_orig;
    int col_diff = col_dest - col_orig;
    int lign_inc = lign_diff / abs(lign_diff);
    int col_inc = col_diff / abs(col_diff);
    int lign_cur = lign_orig + lign_inc;
    int col_cur = col_orig + col_inc;
    while (lign_cur != lign_dest && col_cur != col_dest)
    {
        if (board[lign_cur][col_cur] != nullptr && lign_cur != lign_dest && col_cur != col_dest)
        {
            return 0;
        }
        lign_cur += lign_inc;
        col_cur += col_inc;
    }
    return 1;
}

int Board::isPathClearRook(int col_orig, int lign_orig, int col_dest, int lign_dest)
{
    // if move is to the right
    if (col_dest > col_orig)
    {
        for (int i(col_orig + 1); i < col_dest; i++)
        {
            if (board[lign_orig][i] != nullptr && i != col_dest)
            {
                return 0;
            }
        }
    }
    // if move is to the left
    else if (col_dest < col_orig)
    {
        for (int i(col_orig - 1); i > col_dest; i--)
        {
            if (board[lign_orig][i] != nullptr && i != col_dest)
            {
                return 0;
            }
        }
    }
    // if move is to the top
    else if (lign_dest > lign_orig)
    {
        for (int i(lign_orig + 1); i < lign_dest; i++)
        {
            if (board[i][col_orig] != nullptr && i != lign_dest)
            {
                return 0;
            }
        }
    }
    // if move is to the bottom
    else if (lign_dest < lign_orig)
    {
        for (int i(lign_orig - 1); i > lign_dest; i--)
        {
            if (board[i][col_orig] != nullptr && i != lign_dest)
            {
                return 0;
            }
        }
    }
    return 1;
}

int Board::isPathClearQueen(int col_orig, int lign_orig, int col_dest, int lign_dest)
{
    // check if the movement diagonal or horizontal or vertical
    if (lign_orig == lign_dest || col_orig == col_dest)
    {
        // check if the path is clear
        if (isPathClearRook(col_orig, lign_orig, col_dest, lign_dest) == 0)
        {
            return 0;
        }
    }
    else
    {
        // check if the path is clear
        if (isPathClearBishop(col_orig, lign_orig, col_dest, lign_dest) == 0)
        {
            return 0;
        }
    }
    return 1;
}

int Board::isPathClearPawn(int col_orig, int lign_orig, int col_dest, int lign_dest)
{
    if (board[lign_orig][col_orig]->get_name() == " \u2659 ")
    {
        // check if the path is clear
        if (isPathClearPawnWhite(col_orig, lign_orig, col_dest, lign_dest) == 0)
        {
            return 0;
        }
    }
    else
    {
        // check if the path is clear
        if (isPathClearPawnBlack(col_orig, lign_orig, col_dest, lign_dest) == 0)
        {
            return 0;
        }
    }
    return 1;
}

int Board::isPathClearPawnWhite(int col_orig, int lign_orig, int col_dest, int lign_dest)
{
    if (board[lign_orig][col_orig]->get_position().get_lign() == 1)
    {
        // check if the path is clear
        if (lign_dest == lign_orig + 1)
        {
            if (board[lign_dest][col_dest] == nullptr)
            {
                return 1;
            }
            else
            {
                return 0;
            }
        }
        if (lign_dest == lign_orig + 2)
        {
            if (board[lign_dest][col_dest] == nullptr && board[lign_orig + 1][col_orig] == nullptr)
            {
                return 1;
            }
            else
            {
                return 0;
            }
        }
    }
    else
    {
        if (board[lign_dest][col_dest] == nullptr)
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }
    return 1;
}

int Board::isPathClearPawnBlack(int col_orig, int lign_orig, int col_dest, int lign_dest)
{
    if (board[lign_orig][col_orig]->get_position().get_lign() == 6)
    {
        // check if the path is clear
        if (lign_dest == lign_orig - 1)
        {
            if (board[lign_dest][col_dest] == nullptr)
            {
                return 1;
            }
            else
            {
                return 0;
            }
        }
        if (lign_dest == lign_orig - 2)
        {
            if (board[lign_dest][col_dest] == nullptr && board[lign_orig - 1][col_orig] == nullptr)
            {
                return 1;
            }
            else
            {
                return 0;
            }
        }
    }
    else
    {
        if (board[lign_dest][col_dest] == nullptr)
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }
    return 1;
}

int Board::isPathClear(int col_orig, int lign_orig, int col_dest, int lign_dest)
{
    // check the destination square
    if (destinationSquare(col_orig, lign_orig, col_dest, lign_dest) == 0)
    {
        return 0;
    }
    // check if the piece is a bishop
    if (board[lign_orig][col_orig]->get_name() == " \u265D " || board[lign_orig][col_orig]->get_name() == " \u2657 ")
    {
        return isPathClearBishop(col_orig, lign_orig, col_dest, lign_dest);
    }
    // check if the piece is a rook
    else if (board[lign_orig][col_orig]->get_name() == " \u265C " || board[lign_orig][col_orig]->get_name() == " \u2656 ")
    {
        return isPathClearRook(col_orig, lign_orig, col_dest, lign_dest);
    }
    // check if the piece is a queen
    else if (board[lign_orig][col_orig]->get_name() == " \u265B " || board[lign_orig][col_orig]->get_name() == " \u2655 ")
    {
        return isPathClearQueen(col_orig, lign_orig, col_dest, lign_dest);
    }
    // check if the piece is a pawn
    else if (board[lign_orig][col_orig]->get_name() == " \u2659 " || board[lign_orig][col_orig]->get_name() == " \u265A ")
    {
        return isPathClearPawn(col_orig, lign_orig, col_dest, lign_dest);
    }
    return 1;
}

/**
 * @brief check if there is a piece of the same color in the destination square
 *
 */
int Board::destinationSquare(int col_orig, int lign_orig, int col_dest, int lign_dest)
{
    if (board[lign_dest][col_dest] != nullptr)
    {
        if (board[lign_dest][col_dest]->get_color() == board[lign_orig][col_orig]->get_color())
        {
            cout << "There is a piece of the same color in the destination square" << endl;
            return 0;
        }
    }
    return 1;
}

int Board::pawnIsTaking(int col_orig, int lign_orig, int col_dest, int lign_dest)
{
    if ((lign_dest == lign_orig + 1 && board[lign_orig][col_orig]->get_color() == White) ||
        (lign_dest == lign_orig - 1 && board[lign_orig][col_orig]->get_color() == Black))
    {
        if (board[lign_dest][col_dest] == nullptr)
        {
            return 0;
        }
    }
    {
        // check if the pawn is taking to the right
        if (col_dest == col_orig + 1)
        {
            if (board[lign_dest][col_dest] != nullptr &&
                board[lign_dest][col_dest]->get_color() != board[lign_orig][col_orig]->get_color())
            {
                return 1;
            }
        }
        // check if the pawn is taking to the left
        if (col_dest == col_orig - 1)
        {
            if (board[lign_dest][col_dest] != nullptr &&
                board[lign_dest][col_dest]->get_color() != board[lign_orig][col_orig]->get_color())
            {
                return 1;
            }
        }
    }
    return 0;
}

int Board::isEnPassant(int col_orig, int lign_orig, int col_dest, int lign_dest)
{
    // white pawn is taking
    if (board[lign_orig][col_orig]->get_name() == " \u2659 ")
    {
        if (lign_orig == 4 && lign_dest == 5 && (col_dest == col_orig + 1 || col_dest == col_orig - 1))
        {
            // check the last move
            // check if the pawn is taking to the right
            if (lastMove.StartCol == col_orig + 1 &&
                lastMove.StartLign == 6 &&
                lastMove.EndCol == col_orig + 1 &&
                lastMove.EndLign == 4 &&
                lastMove.piece->get_name() == " \u265F " &&
                col_dest == col_orig + 1)
            {
                return 1;
            }
            // check if the pawn is taking to the left
            if (lastMove.StartCol == col_orig - 1 &&
                lastMove.StartLign == 6 &&
                lastMove.EndCol == col_orig - 1 &&
                lastMove.EndLign == 4 &&
                lastMove.piece->get_name() == " \u265F " &&
                col_dest == col_orig - 1)
            {
                return 1;
            }
        }
    }
    // black pawn is taking
    if (board[lign_orig][col_orig]->get_name() == " \u265F ")
    {
        if (lign_orig == 3 &&
            lign_dest == 2 &&
            (col_dest == col_orig + 1 || col_dest == col_orig - 1))
        {
            // check the last move
            // check if the pawn is taking to the right
            if (lastMove.StartCol == col_orig + 1 &&
                lastMove.StartLign == 1 &&
                lastMove.EndCol == col_orig + 1 &&
                lastMove.EndLign == 3 &&
                lastMove.piece->get_name() == " \u2659 " &&
                col_dest == col_orig + 1)
            {
                return 1;
            }
            // check if the pawn is taking to the left
            if (lastMove.StartCol == col_orig - 1 &&
                lastMove.StartLign == 1 &&
                lastMove.EndCol == col_orig - 1 &&
                lastMove.EndLign == 3 &&
                lastMove.piece->get_name() == " \u2659 " &&
                col_dest == col_orig - 1)
            {
                return 1;
            }
        }
    }
    return 0;
}

/**
 * @brief check if the piece is attacking the opponent king
 * @return int
 */
int Board::isAttackingKing(Piece *piece)
{
    // get the opponent king name
    string king_name, rook_name, bishop_name, queen_name, pawn_name, knight_name;
    if (piece->get_color() == Black)
    {
        king_name = " \u2654 ";
        rook_name = " \u265C ";
        bishop_name = " \u265D ";
        queen_name = " \u265B ";
        pawn_name = " \u265F ";
        knight_name = " \u265E ";
    }
    else
    {
        king_name = " \u265A ";
        rook_name = " \u2656 ";
        bishop_name = " \u2657 ";
        queen_name = " \u2655 ";
        pawn_name = " \u2659 ";
        knight_name = " \u2658 ";
    }

    int lign_orig = piece->get_position().get_lign();
    int col_orig = piece->get_position().get_column();
    // if the piece is a rook
    if (piece->get_name() == rook_name)
    {
        int other_piece = 0;
        // check the right side
        for (int i = col_orig + 1; i < NBCOL; i++)
        {
            if (board[lign_orig][i] != nullptr &&
                board[lign_orig][i]->get_name() != king_name)
            {
                other_piece = 1;
                break;
            }
            if (board[lign_orig][i] != nullptr &&
                board[lign_orig][i]->get_name() == king_name &&
                other_piece == 0)
            {
                return 1;
            }
        }
        // check the left side
        other_piece = 0;
        for (int i = col_orig - 1; i >= 0; i--)
        {
            if (board[lign_orig][i] != nullptr &&
                board[lign_orig][i]->get_name() != king_name)
            {
                other_piece = 1;
                break;
            }
            if (board[lign_orig][i] != nullptr &&
                board[lign_orig][i]->get_name() == king_name &&
                other_piece == 0)
            {
                return 1;
            }
        }
        // check the top side
        other_piece = 0;
        for (int i = lign_orig - 1; i >= 0; i--)
        {
            if (board[i][col_orig] != nullptr &&
                board[i][col_orig]->get_name() != king_name)
            {
                other_piece = 1;
                break;
            }
            if (board[i][col_orig] != nullptr &&
                board[i][col_orig]->get_name() == king_name &&
                other_piece == 0)
            {
                return 1;
            }
        }
        // check the bottom side
        other_piece = 0;
        for (int i = lign_orig + 1; i < NBLIGN; i++)
        {
            if (board[i][col_orig] != nullptr &&
                board[i][col_orig]->get_name() != king_name)
            {
                other_piece = 1;
                break;
            }
            if (board[i][col_orig] != nullptr &&
                board[i][col_orig]->get_name() == king_name &&
                other_piece == 0)
            {
                return 1;
            }
        }
    }
    // if the piece is a bishop
    if (piece->get_name() == bishop_name)
    {
        int other_piece = 0;
        // check the top right side
        for (int i = 1; i < NBCOL - col_orig; i++)
        {
            if (lign_orig - i < 0 || col_orig + i >= NBCOL)
            {
                break;
            }
            if (board[lign_orig - i][col_orig + i] != nullptr &&
                board[lign_orig - i][col_orig + i]->get_name() != king_name)
            {
                other_piece = 1;
                break;
            }
            if (board[lign_orig - i][col_orig + i] != nullptr &&
                board[lign_orig - i][col_orig + i]->get_name() == king_name &&
                other_piece == 0)
            {
                return 1;
            }
        }
        // check the bottom right side
        other_piece = 0;
        for (int i = 1; i < NBLIGN - lign_orig; i++)
        {
            if (lign_orig + i >= NBLIGN || col_orig + i >= NBCOL)
            {
                break;
            }
            if (board[lign_orig + i][col_orig + i] != nullptr &&
                board[lign_orig + i][col_orig + i]->get_name() != king_name)
            {
                other_piece = 1;
                break;
            }
            if (board[lign_orig + i][col_orig + i] != nullptr &&
                board[lign_orig + i][col_orig + i]->get_name() == king_name &&
                other_piece == 0)
            {
                return 1;
            }
        }
        // check the top left side
        other_piece = 0;
        for (int i = 1; i < col_orig; i++)
        {
            if (lign_orig - i < 0 || col_orig - i < 0)
            {
                break;
            }
            if (board[lign_orig - i][col_orig - i] != nullptr &&
                board[lign_orig - i][col_orig - i]->get_name() != king_name)
            {
                other_piece = 1;
                break;
            }
            if (board[lign_orig - i][col_orig - i] != nullptr &&
                board[lign_orig - i][col_orig - i]->get_name() == king_name &&
                other_piece == 0)
            {
                return 1;
            }
        }
        // check the bottom left side
        other_piece = 0;
        for (int i = 1; i < NBLIGN - lign_orig; i++)
        {
            if (lign_orig + i >= NBLIGN || col_orig - i < 0)
            {
                break;
            }
            if (board[lign_orig + i][col_orig - i] != nullptr &&
                board[lign_orig + i][col_orig - i]->get_name() != king_name)
            {
                other_piece = 1;
                break;
            }
            if (board[lign_orig + i][col_orig - i] != nullptr &&
                board[lign_orig + i][col_orig - i]->get_name() == king_name &&
                other_piece == 0)
            {
                return 1;
            }
        }
    }
    // if the piece is a queen
    if (piece->get_name() == queen_name)
    {
        int other_piece = 0;
        // check the right side
        for (int i = col_orig + 1; i < NBCOL; i++)
        {
            if (board[lign_orig][i] != nullptr &&
                board[lign_orig][i]->get_name() != king_name)
            {
                other_piece = 1;
                break;
            }
            if (board[lign_orig][i] != nullptr &&
                board[lign_orig][i]->get_name() == king_name &&
                other_piece == 0)
            {
                return 1;
            }
        }
        // check the left side
        other_piece = 0;
        for (int i = col_orig - 1; i >= 0; i--)
        {
            if (board[lign_orig][i] != nullptr &&
                board[lign_orig][i]->get_name() != king_name)
            {
                other_piece = 1;
                break;
            }
            if (board[lign_orig][i] != nullptr &&
                board[lign_orig][i]->get_name() == king_name &&
                other_piece == 0)
            {
                return 1;
            }
        }
        // check the top side
        other_piece = 0;
        for (int i = lign_orig - 1; i >= 0; i--)
        {
            if (board[i][col_orig] != nullptr &&
                board[i][col_orig]->get_name() != king_name)
            {
                other_piece = 1;
                break;
            }
            if (board[i][col_orig] != nullptr &&
                board[i][col_orig]->get_name() == king_name &&
                other_piece == 0)
            {
                return 1;
            }
        }
        // check the bottom side
        other_piece = 0;
        for (int i = lign_orig + 1; i < NBLIGN; i++)
        {
            if (board[i][col_orig] != nullptr &&
                board[i][col_orig]->get_name() != king_name)
            {
                other_piece = 1;
                break;
            }
            if (board[i][col_orig] != nullptr &&
                board[i][col_orig]->get_name() == king_name &&
                other_piece == 0)
            {
                return 1;
            }
        }
        // check the top right side
        other_piece = 0;
        for (int i = 1; i < NBCOL - col_orig; i++)
        {
            if (lign_orig - i < 0 || col_orig + i >= NBCOL)
            {
                break;
            }
            if (board[lign_orig - i][col_orig + i] != nullptr &&
                board[lign_orig - i][col_orig + i]->get_name() != king_name)
            {
                other_piece = 1;
                break;
            }
            if (board[lign_orig - i][col_orig + i] != nullptr &&
                board[lign_orig - i][col_orig + i]->get_name() == king_name &&
                other_piece == 0)
            {
                return 1;
            }
        }
        // check the bottom right side
        other_piece = 0;
        for (int i = 1; i < NBLIGN - lign_orig; i++)
        {
            if (lign_orig + i >= NBLIGN || col_orig + i >= NBCOL)
            {
                break;
            }
            if (board[lign_orig + i][col_orig + i] != nullptr &&
                board[lign_orig + i][col_orig + i]->get_name() != king_name)
            {
                other_piece = 1;
                break;
            }
            if (board[lign_orig + i][col_orig + i] != nullptr &&
                board[lign_orig + i][col_orig + i]->get_name() == king_name &&
                other_piece == 0)
            {
                return 1;
            }
        }
        // check the top left side
        other_piece = 0;
        for (int i = 1; i < col_orig; i++)
        {
            if (lign_orig - i < 0 || col_orig - i < 0)
            {
                break;
            }
            if (board[lign_orig - i][col_orig - i] != nullptr &&
                board[lign_orig - i][col_orig - i]->get_name() != king_name)
            {
                other_piece = 1;
                break;
            }
            if (board[lign_orig - i][col_orig - i] != nullptr &&
                board[lign_orig - i][col_orig - i]->get_name() == king_name &&
                other_piece == 0)
            {
                return 1;
            }
        }
        // check the bottom left side
        other_piece = 0;
        for (int i = 1; i < NBLIGN - lign_orig; i++)
        {
            if (lign_orig + i >= NBLIGN || col_orig - i < 0)
            {
                break;
            }
            if (board[lign_orig + i][col_orig - i] != nullptr &&
                board[lign_orig + i][col_orig - i]->get_name() != king_name)
            {
                other_piece = 1;
                break;
            }
            if (board[lign_orig + i][col_orig - i] != nullptr &&
                board[lign_orig + i][col_orig - i]->get_name() == king_name &&
                other_piece == 0)
            {
                return 1;
            }
        }
    }
    // if the piece is a knight
    if (piece->get_name() == knight_name)
    {
        // check the right side
        if (col_orig + 2 < NBCOL && lign_orig - 1 >= 0 &&
            board[lign_orig - 1][col_orig + 2] != nullptr &&
            board[lign_orig - 1][col_orig + 2]->get_name() == king_name)
        {
            return 1;
        }
        if (col_orig + 2 < NBCOL && lign_orig + 1 < NBLIGN &&
            board[lign_orig + 1][col_orig + 2] != nullptr &&
            board[lign_orig + 1][col_orig + 2]->get_name() == king_name)
        {
            return 1;
        }
        // check the left side
        if (col_orig - 2 >= 0 && lign_orig - 1 >= 0 &&
            board[lign_orig - 1][col_orig - 2] != nullptr &&
            board[lign_orig - 1][col_orig - 2]->get_name() == king_name)
        {
            return 1;
        }
        if (col_orig - 2 >= 0 && lign_orig + 1 < NBLIGN &&
            board[lign_orig + 1][col_orig - 2] != nullptr &&
            board[lign_orig + 1][col_orig - 2]->get_name() == king_name)
        {
            return 1;
        }
        // check the top side
        if (lign_orig - 2 >= 0 && col_orig - 1 >= 0 &&
            board[lign_orig - 2][col_orig - 1] != nullptr &&
            board[lign_orig - 2][col_orig - 1]->get_name() == king_name)
        {
            return 1;
        }
        if (lign_orig - 2 >= 0 && col_orig + 1 < NBCOL &&
            board[lign_orig - 2][col_orig + 1] != nullptr &&
            board[lign_orig - 2][col_orig + 1]->get_name() == king_name)
        {
            return 1;
        }
        // check the bottom side
        if (lign_orig + 2 < NBLIGN && col_orig - 1 >= 0 &&
            board[lign_orig + 2][col_orig - 1] != nullptr &&
            board[lign_orig + 2][col_orig - 1]->get_name() == king_name)
        {
            return 1;
        }
        if (lign_orig + 2 < NBLIGN && col_orig + 1 < NBCOL &&
            board[lign_orig + 2][col_orig + 1] != nullptr &&
            board[lign_orig + 2][col_orig + 1]->get_name() == king_name)
        {
            return 1;
        }
    }
    // if the piece is a white pawn
    if (piece->get_name() == pawn_name && piece->get_color() == White)
    {
        // check the two squares the pawn is attacking
        if (lign_orig + 1 >= 0 && col_orig + 1 < NBCOL &&
            board[lign_orig + 1][col_orig + 1] != nullptr &&
            board[lign_orig + 1][col_orig + 1]->get_name() == king_name)
        {
            return 1;
        }
        if (lign_orig + 1 >= 0 && col_orig - 1 >= 0 &&
            board[lign_orig + 1][col_orig - 1] != nullptr &&
            board[lign_orig + 1][col_orig - 1]->get_name() == king_name)
        {
            return 1;
        }
    }
    // if the piece is a black pawn
    if (piece->get_name() == pawn_name && piece->get_color() == Black)
    {
        // check the two squares the pawn is attacking
        if (lign_orig - 1 >= 0 && col_orig + 1 < NBCOL &&
            board[lign_orig - 1][col_orig + 1] != nullptr &&
            board[lign_orig - 1][col_orig + 1]->get_name() == king_name)
        {
            return 1;
        }
        if (lign_orig - 1 >= 0 && col_orig - 1 >= 0 &&
            board[lign_orig - 1][col_orig - 1] != nullptr &&
            board[lign_orig - 1][col_orig - 1]->get_name() == king_name)
        {
            return 1;
        }
    }
    return 0;
}

int Board::isKingInCheck(Color color)
{
    // check if a piece is attacking the king
    for (int i = 0; i < NBLIGN; i++)
    {
        for (int j = 0; j < NBCOL; j++)
        {
            if (board[i][j] != nullptr)
            {
                if (board[i][j]->get_color() != color)
                {
                    if (isAttackingKing(board[i][j]))
                    {
                        return 1;
                    }
                }
            }
        }
    }
    return 0;
}

/**
 * @brief create temporary board to check if the king will be in check after the move
 *  if the king is in check after the move, the move is not possible
 * @param piece
 * @param lign_orig
 * @param col_orig
 * @param lign_dest
 * @param col_dest
 * @return int 1 if the king is in check after the move, 0 otherwise
 */
int Board::kingWillBeInCheckAfterMove(int lign_orig, int col_orig, int lign_dest, int col_dest)
{

    // simulate the move, save the piece in case it's a taking move, also check if it's en passant
    Piece *piece_to_save = board[lign_dest][col_dest];
    Piece *piece = board[lign_orig][col_orig];
    board[lign_orig][col_orig] = nullptr;
    board[lign_dest][col_dest] = piece;
    // set the new position of the piece
    piece->setPosition(lign_dest, col_dest);
    // check if the king is in check
    int check = isKingInCheck(piece->get_color());
    // undo the move
    board[lign_orig][col_orig] = piece;
    board[lign_dest][col_dest] = piece_to_save;
    piece->setPosition(lign_orig, col_orig);
    return check;
}

Piece ***Board::getBoard()
{
    return (Piece ***)board;
}

int simulateMove(Piece ***board, int lign_orig, int col_orig, int lign_dest, int col_dest)
{
    // create a temporary board
    Board *temp_board = new Board();
    // put the pieces on the temporary board
    for (int i = 0; i < NBLIGN; i++)
    {
        for (int j = 0; j < NBCOL; j++)
        {
            if (board[i][j] != nullptr)
            {
                temp_board->getBoard()[i][j] = board[i][j]->clone();
            }
            else
                temp_board->getBoard()[i][j] = nullptr;
        }
    }
    // move the piece on the temporary board
    temp_board->move(lign_orig, col_orig, lign_dest, col_dest);
    // check if the king is in check after the move
    if (temp_board->isKingInCheck(board[lign_dest][col_dest]->get_color()))
    {
        delete temp_board;
        return 1;
    }
    delete temp_board;
    return 0;
}

int Board::isPromotion(int lign_orig, int col_orig, int lign_dest, int col_dest)
{
    string pawn_name;
    // get pawn name in fonction of the color
    if (board[lign_orig][col_orig]->get_color() == White)
    {
        pawn_name = " \u2659 ";
    }
    else
    {
        pawn_name = " \u265F ";
    }
    // check if the piece is a pawn
    if (board[lign_orig][col_orig]->get_name() == pawn_name)
    {
        // check if the pawn is on the last line
        if (board[lign_orig][col_orig]->get_color() == White && lign_dest == NBLIGN - 1)
        {
            return 1;
        }
        if (board[lign_orig][col_orig]->get_color() == Black && lign_dest == 0)
        {
            return 1;
        }
    }
    // not use col_dest
    UNUSED(col_dest);
    return 0;
}

/**
 * @brief check if the move is possible, ask the user for the promotion piece, and apply the move
 *
 * @param lign_orig
 * @param col_orig
 * @param lign_dest
 * @param col_dest
 * @return int
 */
int Board::promotion(int lign_orig, int col_orig, int lign_dest, int col_dest)
{
    string piece_name;
    cout << "Choose the piece you want to promote your pawn to :" << endl;
    cout << "1. Queen" << endl;
    cout << "2. Rook" << endl;
    cout << "3. Bishop" << endl;
    cout << "4. Knight" << endl;
    cin >> piece_name;
    // check if the piece name is valid
    while (piece_name != "Queen" && piece_name != "Rook" && piece_name != "Bishop" && piece_name != "Knight")
    {
        cout << "Invalid piece name, please choose a valid piece name :" << endl;
        cout << "1. Queen" << endl;
        cout << "2. Rook" << endl;
        cout << "3. Bishop" << endl;
        cout << "4. Knight" << endl;
        cin >> piece_name;
    }
    // create the piece
    Piece *piece = nullptr;
    Color color = board[lign_orig][col_orig]->get_color();
    if (piece_name == "Queen" && color == White)
    {
        piece = new Queen(color, " \u2655 ", Square(lign_dest, col_dest));
    }
    else if (piece_name == "Queen" && color == Black)
    {
        piece = new Queen(color, " \u265B ", Square(lign_dest, col_dest));
    }
    else if (piece_name == "Rook" && color == White)
    {
        piece = new Rook(color, " \u2656 ", Square(lign_dest, col_dest));
    }
    else if (piece_name == "Rook" && color == Black)
    {
        piece = new Rook(color, " \u265C ", Square(lign_dest, col_dest));
    }
    else if (piece_name == "Bishop" && color == White)
    {
        piece = new Bishop(color, " \u2657 ", Square(lign_dest, col_dest));
    }
    else if (piece_name == "Bishop" && color == Black)
    {
        piece = new Bishop(color, " \u265D ", Square(lign_dest, col_dest));
    }
    else if (piece_name == "Knight" && color == White)
    {
        piece = new Knight(color, " \u2658 ", Square(lign_dest, col_dest));
    }
    else if (piece_name == "Knight" && color == Black)
    {
        piece = new Knight(color, " \u265E ", Square(lign_dest, col_dest));
    }
    // move the piece
    move(lign_orig, col_orig, lign_dest, col_dest);
    // delete the pawn
    delete board[lign_orig][col_orig];
    board[lign_orig][col_orig] = nullptr;
    // put the new piece on the board
    board[lign_dest][col_dest] = piece;
    piece->setPosition(lign_dest, col_dest);

    // save last move
    lastMove.piece = board[lign_orig][col_orig];
    lastMove.StartCol = col_orig;
    lastMove.StartLign = lign_orig;
    lastMove.EndCol = col_dest;
    lastMove.EndLign = lign_dest;

    // test if the king is in check now, if yes, ask the player to move the king out of the check
    // get the other color
    Color otherColor;
    if (board[lign_dest][col_dest]->get_color() == White)
    {
        otherColor = Black;
    }
    else
    {
        otherColor = White;
    }
    if (isKingInCheck(otherColor))
    {
        cout << "Check !" << endl;
    }

    return 1;
}

// int Board::isCheckmate(Color color)
// {
//     // check if the king is in check
//     if (!isKingInCheck(color))
//     {
//         return 0;
//     }

//     // check if the king can move out of the check
// }

/**
 * @brief  check if the king can castle
 *
 * @param color  the color of the king
 * @return int 1 if the king can only castle short,
 *             2 if the king can only castle long,
 *             3 if the king can castle both ways,
 *             0 if the king can't castle
 */
int Board::canCastle(Color color)
{

    int short_castle = 0;
    int long_castle = 0;
    if (color == White)
    {
        if (whiteKingCastled == 1)
        {
            return 0;
        }
        // short castling
        if (board[0][4] != nullptr && board[0][7] != nullptr)
        {
            if (board[0][4]->get_name() == " \u2654 " &&
                board[0][7]->get_name() == " \u2656 " &&
                board[0][5] == nullptr && board[0][6] == nullptr &&
                board[0][4]->get_hasMoved() == 0 && board[0][7]->get_hasMoved() == 0)
            {
                short_castle = 1;
            }
        }
        // long castling
        if (board[0][4] != nullptr && board[0][0] != nullptr)
        {
            if (board[0][4]->get_name() == " \u2654 " &&
                board[0][0]->get_name() == " \u2656 " &&
                board[0][1] == nullptr && board[0][2] == nullptr && board[0][3] == nullptr &&
                board[0][4]->get_hasMoved() == 0 && board[0][0]->get_hasMoved() == 0)
            {
                long_castle = 2;
            }
        }
        return short_castle + long_castle;
    }
    else
    {
        if (blackKingCastled == 1)
        {
            return 0;
        }
        // short castling
        if (board[7][4] != nullptr && board[7][7] != nullptr)
        {
            if (board[7][4]->get_name() == " \u265A " &&
                board[7][7]->get_name() == " \u265C " &&
                board[7][5] == nullptr && board[7][6] == nullptr &&
                board[7][4]->get_hasMoved() == 0 && board[7][7]->get_hasMoved() == 0)
            {
                short_castle = 1;
            }
        }
        // long castling
        if (board[7][4] != nullptr && board[7][0] != nullptr)
        {
            if (board[7][4]->get_name() == " \u265A " &&
                board[7][0]->get_name() == " \u265C " &&
                board[7][1] == nullptr && board[7][2] == nullptr && board[7][3] == nullptr &&
                board[7][4]->get_hasMoved() == 0 && board[7][0]->get_hasMoved() == 0)
            {
                long_castle = 2;
            }
        }
    }
    return short_castle + long_castle;
}

int Board::shortCastling(Color color)
{
    // check if the king is in check
    if (isKingInCheck(color))
    {
        cout << "You can't castle out of check" << endl;
        return 0;
    }
    // check if the king can castle
    if (canCastle(color) != 1 && canCastle(color) != 3)
    {
        cout << "You can't castle" << endl;
        return 0;
    }
    if (color == White)
    {
        // move the rook
        board[0][5] = board[0][7];
        board[0][7] = nullptr;
        board[0][5]->setPosition(0, 5);
        // move the king
        board[0][6] = board[0][4];
        board[0][4] = nullptr;
        board[0][6]->setPosition(0, 6);
        whiteKingPos = {0, 6};
        // set the hasMoved flag
        board[0][5]->setHasMoved(1);
        board[0][6]->setHasMoved(1);
        // check if the king is in check
        if (isKingInCheck(color))
        {
            cout << "You can't castle into check" << endl;
            // move the king back
            board[0][4] = board[0][6];
            board[0][6] = nullptr;
            board[0][4]->setPosition(0, 4);
            whiteKingPos = {0, 4};
            // move the rook back
            board[0][7] = board[0][5];
            board[0][5] = nullptr;
            board[0][7]->setPosition(0, 7);
            // set the hasMoved flag
            board[0][4]->setHasMoved(0);
            board[0][7]->setHasMoved(0);

            return 0;
        }
        // save last move
        lastMove.piece = board[whiteKingPos.get_lign()][whiteKingPos.get_column()];
        lastMove.StartCol = 4;
        lastMove.StartLign = 0;
        lastMove.EndCol = 6;
        lastMove.EndLign = 0;
    }
    else if (color == Black)
    {
        // move the rook
        board[7][5] = board[7][7];
        board[7][7] = nullptr;
        board[7][5]->setPosition(7, 5);
        // move the king
        board[7][6] = board[7][4];
        board[7][4] = nullptr;
        board[7][6]->setPosition(7, 6);
        blackKingPos = {7, 6};
        // set the hasMoved flag
        board[7][5]->setHasMoved(1);
        board[7][6]->setHasMoved(1);
        // check if the king is in check
        if (isKingInCheck(color))
        {
            cout << "You can't castle into check" << endl;
            // move the king back
            board[7][4] = board[7][6];
            board[7][6] = nullptr;
            board[7][4]->setPosition(7, 4);
            blackKingPos = {7, 4};
            // move the rook back
            board[7][7] = board[7][5];
            board[7][5] = nullptr;
            board[7][7]->setPosition(7, 7);
            // set the hasMoved flag
            board[7][4]->setHasMoved(0);
            board[7][7]->setHasMoved(0);

            return 0;
        }
        // save last move
        lastMove.piece = board[blackKingPos.get_lign()][blackKingPos.get_column()];
        lastMove.StartCol = 4;
        lastMove.StartLign = 7;
        lastMove.EndCol = 5;
        lastMove.EndLign = 7;
    }
    return 1;
}

int Board::longCastling(Color color)
{
    // check if the king is in check
    if (isKingInCheck(color))
    {
        cout << "You can't castle out of check" << endl;
        return 0;
    }
    // check if the king can castle
    if (canCastle(color) != 2 && canCastle(color) != 3)
    {
        cout << "You can't castle long " << endl;
        return 0;
    }

    if (color == White)
    {
        // move the rook
        board[0][3] = board[0][0];
        board[0][0] = nullptr;
        board[0][3]->setPosition(0, 3);
        // move the king
        board[0][2] = board[0][4];
        board[0][4] = nullptr;
        board[0][2]->setPosition(0, 2);
        whiteKingPos = {0, 2};
        // set the hasMoved flag
        board[0][2]->setHasMoved(1);
        board[0][3]->setHasMoved(1);
        // check if the king is in check
        if (isKingInCheck(color))
        {
            cout << "You can't castle into check" << endl;
            // move the king back
            board[0][4] = board[0][2];
            board[0][2] = nullptr;
            board[0][4]->setPosition(0, 4);
            whiteKingPos = {0, 4};
            // move the rook back
            board[0][0] = board[0][3];
            board[0][3] = nullptr;
            board[0][0]->setPosition(0, 0);
            // set the hasMoved flag
            board[0][4]->setHasMoved(0);
            board[0][0]->setHasMoved(0);

            return 0;
        }
        // save last move
        lastMove.piece = board[whiteKingPos.get_lign()][whiteKingPos.get_column()];
        lastMove.StartCol = 4;
        lastMove.StartLign = 0;
        lastMove.EndCol = 3;
        lastMove.EndLign = 0;
    }
    else if (color == Black)
    {
        // move the rook
        board[7][3] = board[7][0];
        board[7][0] = nullptr;
        board[7][3]->setPosition(7, 3);
        // move the king
        board[7][2] = board[7][4];
        board[7][4] = nullptr;
        board[7][2]->setPosition(7, 2);
        blackKingPos = {7, 2};
        // set the hasMoved flag
        board[7][2]->setHasMoved(1);
        board[7][3]->setHasMoved(1);
        // check if the king is in check
        if (isKingInCheck(color))
        {
            cout << "You can't castle into check" << endl;
            // move the king back
            board[7][4] = board[7][2];
            board[7][2] = nullptr;
            board[7][4]->setPosition(7, 4);
            // move the rook back
            board[7][0] = board[7][3];
            board[7][3] = nullptr;
            board[7][0]->setPosition(7, 0);
            // set the hasMoved flag
            board[7][4]->setHasMoved(0);
            board[7][0]->setHasMoved(0);

            return 0;
        }
        // save last move
        lastMove.piece = board[blackKingPos.get_lign()][blackKingPos.get_column()];
        lastMove.StartCol = 4;
        lastMove.StartLign = 7;
        lastMove.EndCol = 3;
        lastMove.EndLign = 7;
    }
    return 1;
}
