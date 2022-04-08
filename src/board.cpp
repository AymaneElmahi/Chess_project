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

    // check if the path is clear
    if (isPathClear(col_orig, lign_orig, col_dest, lign_dest) == 0)
    {
        cout << "Path is not clear" << endl;
        return 0;
    }

    board[lign_dest][col_dest] = board[lign_orig][col_orig];
    board[lign_orig][col_orig] = nullptr;
    board[lign_dest][col_dest]->setPosition(col_dest, lign_dest);

    return 1;
}

Board::Board()
{

    allocMemBoard(); // --> alloue un tableau équivalent à un Piece *[8][8]
                     //     en initialisant les cases à nullptr
                     //     et alloue des vecteurs whitePieces, blackPieces, Pawnsb
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

    // allocation des Pawns
    for (unsigned char i(0); i < NBCOL; i++)
    {
        whitePawns[i] = new Pawn(White, " \u2659 ", Square(1, i));
        blackPawns[i] = new Pawn(Black, " \u265F ", Square(6, i));
    }
    // Pose des pieces en position initiale
    // pose des pieces White
    for (unsigned char i(0); i < NBCOL; i++)
    // met à jour le tableau Board, à la case donnée par
    // la position courante de la pièce obtenue avec
    // whitePieces[i]->get_pos(),
    // avec le pointeur vers la pièce (whitePieces[i])
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
    if (lign_dest == lign_orig + 1)
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
