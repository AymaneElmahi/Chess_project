#include "board.hpp"
#include "piece.hpp"
#include "bishop.hpp"
#include "knight.hpp"
#include "pawn.hpp"
#include "rook.hpp"
#include "king.hpp"
#include "queen.hpp"

class Game
{
protected:
    Board board;
    Color turn;

public:
    /**
     * @brief Get the Board object
     *
     * @return Board
     */
    Board getBoard();

    /**
     * @brief move the piece on the board
     *
     * @param startingPos
     * @param endingPos
     * @return int
     */
    int move(string startingPos, string endingPos);

    /**
     * @brief display the board
     *
     */
    void affiche();

    /**
     * @brief get the turn
     *
     * @param turn
     */
    Color getTurn();

    /**
     * @brief set the turn
     *
     * @param turn
     */
    void setTurn(Color turn);

    /**
     * @brief display the board at the end
     *
     * @return int
     */
    int displayEndingPosition();

    /**
     * @brief castle
     *
     * @return int
     */
    int castle(string movement);
};