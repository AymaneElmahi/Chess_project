#include <iostream>
#include "macros.hpp"
#include "color.hpp"

#include "board.hpp"
#include "game.hpp"

using namespace std;

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
        }
        else
            stop = true;
    } while (!stop);
}
