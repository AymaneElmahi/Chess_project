#include "board.hpp"
#include "piece.hpp"
#include "macros.hpp"

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

void Board::putPiece(Piece *piece, Square position)
{
    board[position.get_lign()][position.get_column()] = piece;
}

void Board::move(int lign_orig, int col_orig, int lign_dest, int col_dest)
{
    board[lign_dest][col_dest] = board[lign_orig][col_orig];
    board[lign_orig][col_orig] = nullptr;
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
