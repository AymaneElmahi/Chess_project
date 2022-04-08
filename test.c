#include <iostream>
#include <string>

using namespace std;

/**
 * @brief open game_tests.txt, run chess.cpp and read line by line and input them to console
 *
 */
int main()
{
    string line;
    ifstream myfile("game_tests.txt");
    if (myfile.is_open())
    {
        while (getline(myfile, line))
        {
            cout << line << '\n';
        }
        myfile.close();
    }

    else
        cout << "Unable to open file";

    return 0;
}
