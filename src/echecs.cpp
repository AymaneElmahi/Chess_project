#include <iostream>
#include "macros.hpp"
#include "color.hpp"

#include "board.hpp"
#include "game.hpp"

using namespace std;

#include <regex>

int is_valid_move(string move)
{
    regex r("[a-h][1-8][a-h][1-8]");
    return regex_match(move, r);
}

int is_valid_castling(string move)
{
    regex s("(O|o|0)-(O|o|0)");
    regex l("(O|o|0)-(O|o|0)-(O|o|0)");
    return regex_match(move, s) || regex_match(move, l);
}

int main()
{
    Game myGame;
    myGame.setTurn(White);
    string movement;
    int castled = 0;
    bool stop(false);
    myGame.affiche();
    do
    {
        cout << "Coup (eg. a1a8) ? ";
        cin >> movement;

        if (movement != "/quit")
        {
            if (!is_valid_move(movement) && !is_valid_castling(movement))
            {
                cout << "Invalid move" << endl;
                continue;
            }
            // check if it's a castle
            if (movement == "O-O" || movement == "O-O-O")
            {
                if (myGame.castle(movement) == 1)
                {
                    myGame.affiche();
                    castled = 1;
                }
            }
            if (castled == 0)
            { // découper case origine et destination
                string orig = movement.substr(0, 2);
                string dest = movement.substr(2, 2);
                if (myGame.move(orig, dest) == 1)
                {
                    myGame.affiche();
                }
            }
            castled = 0;
            // check if it's a stalemate
            if (myGame.getBoard().isStalemate(myGame.getTurn()))
            {
                cout << "Stalemate!" << endl;
                stop = true;
            }
            // check if it's a checkmate
            if (myGame.getBoard().isCheckmate(myGame.getTurn()))
            {
                cout << "Checkmate !" << endl;
                stop = true;
            }
        }
        else
            stop = true;
    } while (!stop);
    // display ending position
    cout << "\n";
    myGame.displayEndingPosition();
    return 0;
}
