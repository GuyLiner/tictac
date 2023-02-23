# Tic Tac Toe Game

Overly complex implementation of Tic Tac Toe

y=mx+b is used for possible diagonal win patterns, and a rotation matrix 

is used for the possible win patterns that happen on the edges, which 

happens to be the rest of the win combinations. This will only work for 

the hardcoded 3x3 grid, but it shouldn't be too hard to scale up.

# How to Play

There are two players and each one will be prompted to select a row 

and a column, until one gets three of their player mark (x's or o's).

# Build from Source

You'll need the Eigen library, it's makes things much easier.

```
git clone https://github.com/GuyLiner/tictac.git
cd tictac/src/
make
./tictac
```
