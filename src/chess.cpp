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
    Color color = White;
    bool stop(false);
    myGame.affiche();
    do
    {
        cout << "Coup (eg. a1a8) ? ";
        cin >> movement;
        if (movement != "/quit")
        {
            // découper case origine et destination
            string orig = movement.substr(0, 2);
            string dest = movement.substr(2, 2);
            if (myGame.move(orig, dest) == 1)
            {
                myGame.affiche();
                if (color == White)
                    color = Black;
                else
                    color = White;
            }
        }
        else
            stop = true;
    } while (!stop);
}
