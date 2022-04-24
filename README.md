### Chess Game in C++

<summary>School project</summary>

1. [Introduction](#introduction)
2. [How to play ?](#How-to-play)
3. [Bugs & TODO](#bugs--todo)

## Introduction

This is a chess game in C++. It is a simple game with a few features. It is not a complete chess game, but it is a good practice for learning OPP. Is it possible to make a complete chess game? I don't know. I think it is possible. I will try someday to make a complete chess game in C++.

## How to play ?

Compile the code with

```bash
make
```

then run the game with

```bash
make run
```

The game is running in a terminal. You can play the game with the keyboard. The program will ask the first player to enter a move (e.g. `e2e4`). The program will then display the board and ask the second player to enter a move. It alternates between the two players.

If the move is not valid, the program will ask the player to enter a new move.

At the end, the program will display the final position of the board in canonical notation.



| dev version used |
| ---------------- |
| g++-9.4.0        |
| -std=c++11       |
| valgrind-3.15.0  |
| -Wall -W -Werror |
| -g -O2 -pedantic |
| -Ofast           |

</details>

## Bugs & TODO

Bugs (final correction version)

- ~~ Some valgrind errors ~~
- The program takes a few seconds to compile.

TODO

- Implement the draw by threefold repetition rule
- Implement the draw by insufficient material rule
- Implement the draw by 50 move rule
- Implement an engine that can play against a human player
- Add an oppening book
- Add an endgame detection
