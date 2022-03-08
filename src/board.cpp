#include "board.hpp"

// Board::Board affiche()
// {
//     string space5 = string(5, ' ');
//     cout << endl;
//     cout << "     a     b     c     d     e     f     g     h    " << endl;
//     cout << "  +-----+-----+-----+-----+-----+-----+-----+-----+" << endl;
//     for (int i(NBCOL - 1); i >= 0; i--)
//     {
//         cout << i + 1 << " "; // numérotation ligne dans affichage
//         for (int j(0); j < NBCOL; j++)
//         {
//             cout << "|";
//             if (echiquier[i][j])
//             {
//                 cout << "\u0020\u0020"; // U+0020 est un esapce utf-8 taille police
//                 echiquier[i][j]->affiche();
//                 cout << "\u0020"
//                      << " ";
//             }
//             else
//                 cout << space5; // 2 ascii spaces
//         }
//         cout << "|\n  +-----+-----+-----+-----+-----+-----+-----+-----+";
//         cout << endl;
//     }
// }