/> Chess Game in C++

<summary>School project</summary>

1. [Introduction](#introduction)
2. [How to play ?](#How-to-play)
3. [License](#License)
4. [Bugs & TODO](#bugs--todo)

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

## License

This Chess engine is licensed under the [GPL-3.0](LICENSE) license. Please see the [license](LICENSE) file for more details.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

- Redistributions of source code must retain the above copyright notice,
  this list of conditions and the following disclaimer.

- Redistributions in binary form must reproduce the above copyright notice,
  this list of conditions and the following disclaimer in the documentation
  and/or other materials provided with the distribution.

- Neither the name of the chess-cli authors nor the names of its
  contributors may be used to endorse or promote products derived from
  this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
POSSIBILITY OF SUCH DAMAGE.

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

TODO

- Implement the draw by threefold repetition rule
- Implement the draw by insufficient material rule
- Implement the draw by 50 move rule
- Implement an engine that can play against a human player
- Add an oppening book
- Add an endgame detection
